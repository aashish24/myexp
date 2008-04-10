#include <gmtl/gmtl.h>
#include<fstream.h>
#include<iostream.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGeoFunctions.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGSimpleTexturedMaterial.h>
#include <OpenSG/OSGImage.h>
#include <OpenSG/OSGMatrix.h>



OSG_USING_NAMESPACE

//The SimpleSceneManager 

SimpleSceneManager *mgr;

//we have a forward declarion here, just to sort the code 
int setupGLUT( int *argc, char *argv[] );

NodePtr localModel (  UInt8* black_white_image_data_recived,  UInt32 width,  int xpoint, int zpoint ,  Pnt3f hit_point, bool event, float scale_value = 1.0);

const float scale = 0.8; 

GroupNodePtr n ;

Matrix geometrymatrix;
 
UInt32  height_colour_image, width_colour_image, width, height;
 
UInt8* black_white_image_data;
 
UInt8* colour_image_data;
 
//double length, breadth;

std::vector<NodePtr> localRoots;



 void keyboard(unsigned char key, int x, int y)
 {
        
       if((key == 'q')||(key == 'Q'))
	{
	        OSG::osgExit();
                exit(0);
        }
         
         if(key == ' ')
         {
                
                Pnt3f hit_point;
                
                Line l;
                
                l = mgr->calcViewRay(x, y);

                IntersectAction *act = IntersectAction::create();
                
                act->setLine( l );
                act->apply( n );
             
                if (act->didHit())
                {
                        hit_point = act->getHitPoint();
                    
                        NodePtr SourceNode = localModel( black_white_image_data, width, 0, 0, hit_point, 1);        ////calling the function //////////////
                        localRoots.push_back(SourceNode);
                }
                
              
                beginEditCP(n, Node::ChildrenFieldMask );
                
                        for(int i=0; i<localRoots.size(); ++i)
                                n.node()->addChild( localRoots[i] );
                
	        endEditCP(n, Node::ChildrenFieldMask );
                
                
                glutPostRedisplay();     
         }
          
 }
 
 
 
 
 NodePtr localModel (  UInt8* black_white_image_data_recived,  UInt32 width,  int xpoint, int zpoint ,  Pnt3f hit_point, bool event, float scale_value)
{
        Matrix m, modelnodematrix, geometry_tempmatrix, modelnode_tempmatrix;
        Vec3f min, max;
        osg::Matrix m1, m2, m3, m4, m5; 
        
        NodePtr model = OSG::SceneFileHandler::the().read("house1_3.3ds");/////defining the first model
	model->updateVolume();
	
		
	TransformPtr transform = Transform::create();                   ///applying transformation and rotaion and scaling first model//
	beginEditCP(transform, Transform::MatrixFieldMask );	        
                m1.setIdentity(); 
                m2.setTranslate( xpoint, 0, zpoint );
                m3.setRotate(Quaternion(Vec3f(1,0,0), -((90.0f*3.14f)/180.0f)));
                m4.setScale(scale_value,scale_value,scale_value);
                m1.mult(m2);
                m1.mult(m3);
                m1.mult(m4);
                transform->setMatrix(m1);
	endEditCP(transform, Transform::MatrixFieldMask );
	
	
	NodePtr transformNode = Node::create();                         ///////creating a node pointer to set the core of models as transform and adding model as child////////////
	beginEditCP(transformNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
	        transformNode->setCore(transform);
	        transformNode->addChild(model);
	       
	endEditCP(transformNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
 
	DynamicVolume vol;
	transformNode->getWorldVolume(vol);
	vol.getBounds ( min, max );                         //////////////original model bounding box/////////////////


  
                  /******placing the  model on the terrian*************/
	double  length,breadth, area, lowestpoint=100000.0, variable;
	UInt32 x, z, j, i;

	length = max[0] - min[0];                                           /////width//
	breadth = max[2] - min[2];                                          ///height///
	area = length * breadth;
      
	if( event)
	{
	        x=( hit_point[0] ) - UInt32(length/2) ;
	        z=( hit_point[2] ) - UInt32(breadth/2);
	       
	}
	else
	{
	        x=( xpoint ) - UInt32(length/2) ;
	        z=( zpoint ) - UInt32(breadth/2);
	}
	
	
	////the two for loops for checking the lowest point condition on the terrain
	////will scan the whole area where the model is going to be placed and then 
	////will place at the lowest point.
	
	
	        if(((x >= 0) && (x<= width)) && ((z >=0) && (z <= height)))
	        {
	
	                for( j = z; j <= (z + breadth); j++ ) 
	                        for( i = x ; i <= (x + length); i++)
	                        {
	                                variable = *(black_white_image_data_recived + ((i * width)+j)) * scale;
	                
	                                if(lowestpoint > variable)
	                                        lowestpoint = variable;
	                         
	                         }      
	        }
	  
	
	
	beginEditCP(transform, Transform::MatrixFieldMask );	        
                m1.setIdentity(); 
                
                if(event)
                        m2.setTranslate( hit_point[0], lowestpoint,  hit_point[2] );
                else
                        m2.setTranslate( xpoint, lowestpoint, zpoint );
                        
                m3.setRotate(Quaternion(Vec3f(1,0,0), -((90.0f * 3.14f) / 180.0f)));
                m4.setScale(scale_value,scale_value,scale_value);
                m1.mult(m2);
                m1.mult(m3);
                m1.mult(m4);
                transform->setMatrix(m1);
	endEditCP(transform, Transform::MatrixFieldMask );

        return transformNode;
      
}

 
 
 ////the function which is generalized which will check the case like whether any part is 
 ////a colour completly and will return a boolean value
 ////it will take the pointer of image and the width and the length and breadth of teh model 
 
 bool checkCase(  UInt32 z_length,  UInt32  x_length,   UInt32 breadth,   UInt32 length,   UInt8* empty_image_data,   UInt32 width_housing_image)
 {
 
        bool not_adjacent= false, adjacent =false;
         for( UInt32 j = z_length; j <= (z_length + breadth); j++ ) 
	 {
	        for( UInt32 i = x_length ; i <= (x_length + length); i++)
	        {
	              
	                                                
	                if( empty_image_data[(width_housing_image * i  * 3) + (j  * 3) + 0] != 255)
	                {              
	                        not_adjacent = true;                 
	                }
	                                                
	                else
	                {
	                        not_adjacent = false;
	                        adjacent=true;
	                                                        
	                        break;
	                }
	                                                       
	                                                
	          } 
	                                        
	          if(adjacent)  
	          break;
	   } 
	   
	   return not_adjacent;          
 }
 


GroupNodePtr createScenegraph(void)
{

        ofstream outputFIle("c:vinay\\terrain_generation\\output.txt");

        /*********** defineing the texture image for texture mapping**********/
        ImagePtr colour_image ;
	colour_image = Image::create();
	colour_image -> read("colour_image.png");
	
	width_colour_image   =  colour_image->getWidth();
	height_colour_image  =  colour_image->getHeight();
	colour_image_data    =  colour_image->getData();
	
		
	
	/*********** defineing the png  image for reading th evaluse from the image**********/
	ImagePtr black_white = Image::create();
	black_white -> read("black_white_image.pgm");	
        
	width  =  black_white->getWidth();	
	height =  black_white->getHeight();	
        black_white_image_data = black_white->getData();

	Real32 wHeight[width][height];
	
	/***************************taking a image which i same size of colour image************************/
	
	ImagePtr housing_image = Image::create();
	//housing_image -> read("housing.png");
	housing_image -> read("housing_128.png");
	UInt32 width_housing_image   =  housing_image->getWidth();
	UInt32 height_housing_image  =  housing_image->getHeight();
	UInt8* housing_image_data  =  housing_image->getData();
	
	//std::cout<< width_housing_image << std::endl;
	//(colour_image_recived[( (width_colour_image * i * 3) + (j * 3) + 0)]) = 255
	UInt32 blue=0;
	for(int x=0; x<height; x++)
		for(int z=0; z<width; z++)
		{
	
	                if(  housing_image_data[(width_housing_image * x * 3) + (z* 3) + 2] == 255)
	                        blue++;
	                        
	        }
	//std::cout<<blue<<std::endl;
	/****************************taking an empty image to use as reference***************************/
	
	ImagePtr empty_image ;
	         empty_image       = Image::create();
	
	beginEditCP(empty_image);
	empty_image->set(Image::OSG_RGB_PF, width_housing_image, height_housing_image);
	endEditCP(empty_image);
	
	UInt8* empty_image_data    =  empty_image->getData();
	
	/**************************************************************************************************/

        /*****************************addding the image part ********************************************/
	SimpleTexturedMaterialPtr tex = SimpleTexturedMaterial::create();
	beginEditCP(tex);
		tex->setImage(colour_image);
	endEditCP(tex);


        /*************storing the image read data in the real32 wHeight*********************************/
	for(int i1=0; i1<height; i1++)
		for(int j=0; j<width; j++)
		{
			wHeight[i1][j] = black_white_image_data[((width*i1)+j)];
			//std::cout<< wHeight[i1][j] << std::endl;
	        }//// looking whether a model is already there so as to check the if other nodel is placed it does not overlap
        /**************************type pointers,,,,,,quads in this case*****************************************/
	GeoPTypesPtr type = GeoPTypesUI8::create();
	beginEditCP(type,GeoPTypesUI8::GeoPropDataFieldMask);
		type->addValue(GL_QUADS);
	endEditCP(type, GeoPTypesUI8::GeoPropDataFieldMask);

        /****************************length pointer*********************************/
	GeoPLengthsPtr len = GeoPLengthsUI32::create();
	beginEditCP(len, GeoPLengthsUI32::GeoPropDataFieldMask);
		len->addValue(((width-1)*(height-1))*4);
	endEditCP(len, GeoPLengthsUI32::GeoPropDataFieldMask);

        /*********************************position and texture adding pointers*****************************/
	GeoPositions3fPtr pos= GeoPositions3f::create();
	GeoTexCoords2fPtr txt= GeoTexCoords2f::create();
	beginEditCP(pos, GeoPositions3f::GeoPropDataFieldMask);
	beginEditCP(txt, GeoTexCoords2f::GeoPropDataFieldMask);
	for(int x=0; x<height; x++)
		for(int z=0; z<width; z++)
			{				
				pos->addValue(Pnt3f(x, wHeight[x][z] * scale, z));
				txt->addValue( Vec2f((Real32(z)/width), (Real32(x)/height)) );
			}
	endEditCP(pos, GeoPositions3f::GeoPropDataFieldMask);
	endEditCP(txt, GeoTexCoords2f::GeoPropDataFieldMask);
	
        /******************************adding indices pointer**********************************/	
	GeoIndicesUI32Ptr indices = GeoIndicesUI32::create();
	beginEditCP(indices, GeoIndicesUI32::GeoPropDataFieldMask);
	for(int z=0; z<(height-1); z++)
		for(int x=0; x<(width-1); x++)
		{
			indices->addValue( x   +z    *width);
			indices->addValue((x+1)+z    *width);
			indices->addValue((x+1)+(z+1)*width);
			indices->addValue( x   +(z+1)*width);
		}
	endEditCP(indices, GeoIndicesUI32::GeoPropDataFieldMask);

        /**************************************adding all the above to the core node*****************************************/
	GeometryPtr geo = Geometry::create();
	beginEditCP(geo, Geometry::TypesFieldMask  |  Geometry::LengthsFieldMask | Geometry::IndicesFieldMask  |  Geometry::PositionsFieldMask | Geometry::TexCoordsFieldMask );

		geo->setTypes( type );
		geo->setLengths( len );
		geo->setIndices( indices );
		geo->setPositions( pos );
		geo->setTexCoords( txt );
		geo->setMaterial( tex );
		geo->setDlistCache( false );
               
	endEditCP(geo, Geometry::TypesFieldMask | Geometry::LengthsFieldMask  |  Geometry::IndicesFieldMask  |  Geometry::PositionsFieldMask  | Geometry::TexCoordsFieldMask );

	calcVertexNormals(geo);


        NodePtr geonode = makeNodeFor(geo);                             ///////////making the main node for the geometry//////////////////////////////
        
        geonode->getToWorld(geometrymatrix);                            /////////////getting the geometry matrix//////////
        
        
        
        
        
        float scale_value = 1.0;
        osg::Matrix m1, m2, m3, m4, m5;	
        Vec3f min, max;	
        
        
        
        NodePtr model = OSG::SceneFileHandler::the().read("house1_3.3ds");/////defining the first model
	model->updateVolume();
	
	
	TransformPtr transform = Transform::create();                   ///applying transformation and rotaion and scaling first model//
	beginEditCP(transform, Transform::MatrixFieldMask );	        
                m1.setIdentity(); 
                m3.setRotate(Quaternion(Vec3f(1,0,0), -((90.0f*3.14f)/180.0f)));
                m4.setScale(scale_value,scale_value,scale_value);
                m1.mult(m3);
                m1.mult(m4);
                transform->setMatrix(m1);
	endEditCP(transform, Transform::MatrixFieldMask );
        
       
	
	NodePtr transformNode = Node::create();                         ///////creating a node pointer to set the core of models as transform and adding model as child////////////
	beginEditCP(transformNode, Node::CoreFieldMask | Node::ChildrenFieldMask);   
	        transformNode->setCore(transform);    
	        transformNode->addChild(model);       
	endEditCP(transformNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        	
        DynamicVolume vol;
	transformNode->getWorldVolume(vol);
	vol.getBounds ( min, max ); 
	  
	 Pnt3f hit_point ;
	 
	UInt32  length,breadth;
	
	length = static_cast<int>(max[0] - min[0]);        // should be ceiled                /////width//
	breadth = static_cast<int>(max[2] - min[2]);                                          ///height///
	
        bool inside = false, not_adjacent= false, adjacent = false, outside = false;	
        
        UInt32 l = length/2;
        UInt32 b = breadth/2;
        UInt32 height_variable,width_variable;
         
         
        /// scanning a image to find whether the area is of a particular colour or not and 
        /// then if the whole are is of that colour then the model is being placed with the boundary condtions of the 
        /// colour.
        for( height_variable = l;   height_variable < height_housing_image - l;   height_variable++)
        {
	        for( width_variable = b;   width_variable < width_housing_image - b;   width_variable++)
	        {     
	        
	                 
	                //checking initially for the co-ordinates whether that co-ordinates has the blue colour so as to place the model          
	                if(  housing_image_data[(width_housing_image * height_variable * 4) + (width_variable * 4) + 2] == 255)
	                        {
	                               
	                                /// finding the initial cordinates of the model so as to scann the complete area
	                                UInt32 x_length = ( height_variable ) -(l);
	                                UInt32 z_length = ( width_variable ) - (b);  
	                              
	                              
	                              
	                                //// looking whether a model is already there so as to check the if other nodel is placed it does not overlap any other model
	                                bool not_red = checkCase(z_length, x_length, breadth, length, empty_image_data, width_housing_image);           
	                                
	                                
	                                
	                                ////now checking the condtion whether the are where the model has to be placed is of desired colour or not
	                                bool blue = checkCase(z_length, x_length, breadth, length, housing_image_data, width_housing_image);
	                               
	                               
	                               
	                               
	                               
	                                ///if satisfying both the conditions like whetehr the area is blue and no other model is been there so that the model to be placed does not overlap
	                                if( (blue == true) && (not_red == true ))
	                                {
	                                        std::cout << "Put house at " << height_variable << "," << width_variable << std::endl;
	                                        ///calling the function to add the model to the desired postion on the terrain
	                                        
	                                        if(width_housing_image == 128)
	                                        {
	                                                 NodePtr SourceNode = localModel( black_white_image_data, width, height_variable / (float)height_housing_image * height_colour_image, 
	                                                                                       width_variable / (float)width_housing_image * width_colour_image,  hit_point, 0,
	                                                                                       width_colour_image / (float)width_housing_image); 
	                                                 
	                                                  localRoots.push_back(SourceNode);
	                                        }
	                                                                                       
	                                                                                       
	                                        else
	                                        {
	                                                NodePtr SourceNode = localModel( black_white_image_data, width, height_variable , 
	                                                                                       width_variable ,  hit_point, 0,
	                                                                                       1.0);        ////calling the function //////////////
	                                                                                 
                                                                        localRoots.push_back(SourceNode);
                                                }
                                                
                                                
                                                for( UInt32 j = z_length; j <= (z_length + breadth); j++ ) 
                                                {
	                                                for( UInt32 i = x_length ; i <= (x_length + length); i++)
	                                                {
	                                                        //clouring that part of terrain where the model is been placed 
	                                                        empty_image_data[(width_housing_image * i  * 3) + (j  * 3) + 0] = 255;
	                                                       
	                                                } 
	                                         }
	                                         
	                                                 
	                                }
	                                
	                        
	                         }              
	                        
	           }
	 }
	           
	   

        
        /**********************************making the final Group node*********************************************/
	n = GroupNodePtr::create();
	beginEditCP(n, Node::ChildrenFieldMask );
	
	n.node()->addChild( geonode );
	for(int i=0; i<localRoots.size(); ++i)
                n.node()->addChild( localRoots[i] ); 
                 
	endEditCP(n, Node::ChildrenFieldMask );

	return n;

}






int main(int argc, char **argv)
{
       
        
        
        
        // Init the OpenSG subsystem
        osgInit(argc,argv);
        
        // We create a GLUT Window (that is almost the same for most applications)
        int winid = setupGLUT(&argc, argv);
        GLUTWindowPtr gwin= GLUTWindow::create();
        gwin->setId(winid);
        gwin->init();

        // That will be our whole scene for now 
        GroupNodePtr scene =createScenegraph();
	
        // Create and setup our little friend - the SSM
        mgr = new SimpleSceneManager;
        mgr->setWindow(gwin );
        mgr->setRoot  (scene.node());
        mgr->showAll();
    
        // Give Control to the GLUT Main Loop
        glutMainLoop();

        return 0;
}




// react to size changes
void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}





// just redraw our scene if this GLUT callback is invoked
void display(void)
{
        mgr->redraw();
        
}



// react to mouse button presses
void mouse(int button, int state, int x, int y)
{
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}





// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}




//The GLUT subsystem is set up here. This is very similar to other GLUT
int setupGLUT(int *argc, char *argv[])
{
        
        glutInit(argc, argv);
        glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
        int winid = glutCreateWindow("Terrain ");
    
        glutDisplayFunc(display);
        glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutReshapeFunc(reshape);
        glutIdleFunc(display);
        glutKeyboardFunc(keyboard);
        return winid;
}
