<!DOCTYPE html>
<!--
/*
 * Copyright (C) 2009 Apple Inc. All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */
 -->
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>Spinning WebGL Box</title>
 
<script src="resources/CanvasMatrix.js" type="text/javascript"> </script>
<script src="resources/utils3d.js" type="text/javascript"> </script>
<script id="vshader" type="x-shader/x-vertex">

    uniform mat4 u_modelViewProjMatrix;
    uniform mat4 u_normalMatrix;
    uniform vec3 lightDir;
 
    attribute vec3 vNormal;
    attribute vec4 vTexCoord;
    attribute vec4 vPosition;
 
    varying float v_Dot;
    varying vec2 v_texCoord;
 
    void main()
    {
        gl_Position = u_modelViewProjMatrix * vPosition;
        v_texCoord = vTexCoord.st;
        vec4 transNormal = u_normalMatrix * vec4(vNormal, 1);
        v_Dot = max(dot(transNormal.xyz, lightDir), 0.0);
    }

</script>
 
 
<script id="fshader" type="x-shader/x-fragment">

    uniform sampler2D sampler2d;
 
    varying float v_Dot;
    varying vec2 v_texCoord;
 
    void main()
    {
        vec2 texCoord = vec2(v_texCoord.s, 1.0 - v_texCoord.t);
        vec4 color = texture2D(sampler2d, texCoord);
        color += vec4(0.1, 0.1, 0.1, 1);
        gl_FragColor = vec4(color.xyz * v_Dot, color.a);
    }

</script>
 
<script>

    function init()
    {
        // Initialize
        var gl = initWebGL(
            // The id of the Canvas Element
            "example",
            // The ids of the vertex and fragment shaders
            "vshader", "fshader", 
            // The vertex attribute names used by the shaders.
            // The order they appear here corresponds to their index
            // used later.
            [ "vNormal", "vColor", "vPosition"],
            // The clear color and depth values
            [ 0, 0, 0, 1 ], 10000);
 
        // Set some uniform variables for the shaders
        gl.uniform3f(gl.getUniformLocation(gl.program, "lightDir"), 0, 0, 1);
        gl.uniform1i(gl.getUniformLocation(gl.program, "sampler2d"), 0);
 
        // Enable texturing
        gl.enable(gl.TEXTURE_2D);
 
        // Create a box. On return 'gl' contains a 'box' property with
        // the BufferObjects containing the arrays for vertices,
        // normals, texture coords, and indices.
        gl.box = makeBox(gl);
 
        // Load an image to use. Returns a WebGLTexture object
        spiritTexture = loadImageTexture(gl, "resources/spirit.jpg");
 
        // Create some matrices to use later and save their locations in the shaders
        gl.mvMatrix = new CanvasMatrix4();
        gl.u_normalMatrixLoc = gl.getUniformLocation(gl.program, "u_normalMatrix");
        gl.normalMatrix = new CanvasMatrix4();
        gl.u_modelViewProjMatrixLoc =
                gl.getUniformLocation(gl.program, "u_modelViewProjMatrix");
        gl.mvpMatrix = new CanvasMatrix4();
 
        // Enable all of the vertex attribute arrays.
        gl.enableVertexAttribArray(0);
        gl.enableVertexAttribArray(1);
        gl.enableVertexAttribArray(2);
 
        // Set up all the vertex attributes for vertices, normals and texCoords
        gl.bindBuffer(gl.ARRAY_BUFFER, gl.box.vertexObject);
        gl.vertexAttribPointer(2, 3, gl.FLOAT, false, 0, 0);
 
        gl.bindBuffer(gl.ARRAY_BUFFER, gl.box.normalObject);
        gl.vertexAttribPointer(0, 3, gl.FLOAT, false, 0, 0);
 
        gl.bindBuffer(gl.ARRAY_BUFFER, gl.box.texCoordObject);
        gl.vertexAttribPointer(1, 2, gl.FLOAT, false, 0, 0);
 
        // Bind the index array
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, gl.box.indexObject);
 
        return gl;
    }
 
    width = -1;
    height = -1;
 
    function reshape(gl)
    {
        var canvas = document.getElementById('example');
        if (canvas.clientWidth == width && canvas.clientHeight == height)
            return;
 
        width = canvas.clientWidth;
        height = canvas.clientHeight;
 
        // Set the viewport and projection matrix for the scene
        gl.viewport(0, 0, width, height);
        gl.perspectiveMatrix = new CanvasMatrix4();
        gl.perspectiveMatrix.lookat(0, 0, 7, 0, 0, 0, 0, 1, 0);
        gl.perspectiveMatrix.perspective(30, width/height, 1, 10000);
    }
 
    function drawPicture(gl)
    {
        // Make sure the canvas is sized correctly.
        reshape(gl);
 
        // Clear the canvas
        gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
 
        // Make a model/view matrix.
        gl.mvMatrix.makeIdentity();
        gl.mvMatrix.rotate(currentAngle, 0,1,0);
        gl.mvMatrix.rotate(20, 1,0,0);
 
        // Construct the normal matrix from the model-view matrix and pass it in
        gl.normalMatrix.load(gl.mvMatrix);
        gl.normalMatrix.invert();
        gl.normalMatrix.transpose();
        gl.uniformMatrix4fv(gl.u_normalMatrixLoc, false,
                            gl.normalMatrix.getAsWebGLFloatArray());
 
        // Construct the model-view * projection matrix and pass it in
        gl.mvpMatrix.load(gl.mvMatrix);
        gl.mvpMatrix.multRight(gl.perspectiveMatrix);
        gl.uniformMatrix4fv(gl.u_modelViewProjMatrixLoc, false,
                            gl.mvpMatrix.getAsWebGLFloatArray());
 
        // Bind the texture to use
        gl.bindTexture(gl.TEXTURE_2D, spiritTexture);
 
        // Draw the cube
        gl.drawElements(gl.TRIANGLES, gl.box.numIndices, gl.UNSIGNED_BYTE, 0);
 
        // Finish up.
        gl.flush();
 
        // Show the framerate
        framerate.snapshot();
 
        currentAngle += incAngle;
        if (currentAngle > 360)
            currentAngle -= 360;
    }
 
    function start()
    {
        var c = document.getElementById("example");
        var w = Math.floor(window.innerWidth * 0.9);
        var h = Math.floor(window.innerHeight * 0.9);
 
        c.width = w;
        c.height = h;
 
        var gl = init();
        currentAngle = 0;
        incAngle = 0.5;
        framerate = new Framerate("framerate");
        setInterval(function() { drawPicture(gl) }, 10);
    }

</script>
<style type="text/css">
    canvas {
        border: 2px solid black;
    }
</style>
</head>
 
<body onload="start()">
<canvas id="example">
    If you're seeing this your web browser doesn't support the &lt;canvas>&gt; element. Ouch!
</canvas>
</body>
 
</html>

Retrieved from "http://www.khronos.org/webgl/wiki/Spirit_Box_Code"
Views

    * Page
    * Discussion
    * View source
    * History

Personal tools

    * Log in / create account

WebGL Links

    * Main page
    * WebGL Message Board
    * Public Mailing List
    * Recent changes
    * Random page
    * Help

Search
 
Toolbox

    * What links here
    * Related changes
    * Special pages
    * Printable version
    * Permanent link

Powered by MediaWiki

    * This page was last modified on 9 December 2009, at 21:58.
    * This page has been accessed 3,315 times.
    * Privacy policy
    * About WebGL Public Wiki
    * Disclaimers

