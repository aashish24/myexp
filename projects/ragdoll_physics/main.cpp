#include "ode/ode.h"

// GMTL (math library includes).
#include "gmtl/Vec.h"
#include "gmtl/Matrix.h"
#include "gmtl/VecOps.h"
#include "gmtl/MatrixOps.h"
#include "gmtl/Xforms.h"

// Sonix (sound library) includes. 

#define  uint32 
#define  int32
#define  int8

#include "snx/sonix.h"
#include "snx/SoundHandle.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <ctime>

#include "drawstuff/drawstuff.h"
#include "texturepath.h"
#include "GL/glut.h"
#include "BmpImage.h"
#include "TgaImage.h"

#define                 drand48()               ((double) (((double) rand()) / ((double) RAND_MAX)))
#define                 BUFSIZE                 512


// Buffer size to store hits.
GLuint                  selectBuf[BUFSIZE];

// Texture object indices. 
GLuint                  glTexIndex;

// Number of manikins
#define                 N_BODIES                12


#define                 STAGE_SIZE              8.0  // in m
static float            TIME_STEP =             0.0005;

// Sponginess
#define                 K_SPRING                1.0
#define                 K_DAMP                  1.0


// ??
double                  timeAccum;
double                  lastTime;


// Variables dealling with mouse use
// used to turn off and on animation and friction aproximation by triggers
static bool             dancing =               false;
static bool             friction =              true;
static int              dance_counter =         0;
static int              step =                  0;
static bool             doInteract =            false;
static int              cursorX;
static int              cursorY;
static int              cursorX2;
static int              cursorY2;


//
static GLuint           wood[1];

static GLuint           name =                  -N_BODIES;
static int              hits;
static int              clicked =               -1;
static int              beat =                  50;

// Names the world in which the collisions take place
static dWorld           dyn_world;


// Density of manikins in kg/m^3  (sun baked dried Chinese Juniper Wood)
static dReal            density =               508;


// Necessary for collisions
static dSpaceID         coll_space_id;
static dJointID         plane2d_joint_ids[N_BODIES];
static dJointGroup      coll_contacts;


// Stairs
static dGeomID          stair1;
static dGeomID          stair2;
static dGeomID          stair3;
static dGeomID          stair4;
static dGeomID          stair5;
static dGeomID          stair6;
static dGeomID          stair7;
static dReal            sides1[]= {2, 1, 0.5};
static dReal            sides2[]= {2, 1, 1};
static dReal            sides3[]= {2, 1, 1.5};
static dReal            sides4[]= {12, 2, 2};


// Names of objects
static dBodyID          torso1[N_BODIES];
static dBodyID          torso2[N_BODIES];
static dBodyID          torso3[N_BODIES];
static dBodyID          head[N_BODIES];
static dBodyID          leftarm1[N_BODIES];
static dBodyID          leftarm2[N_BODIES];
static dBodyID          rightarm1[N_BODIES];
static dBodyID          rightarm2[N_BODIES];
static dBodyID          leftleg1[N_BODIES];
static dBodyID          leftleg2[N_BODIES];
static dBodyID          rightleg1[N_BODIES];
static dBodyID          rightleg2[N_BODIES];
static dBodyID          lefthand[N_BODIES];
static dBodyID          righthand[N_BODIES];
static dBodyID          rightlead_target[N_BODIES];
static dBodyID          leftfollow_target[N_BODIES];


// Names of shapes to be applied to objects later
static dGeomID          torso1_geom[N_BODIES];
static dGeomID          torso2_geom[N_BODIES];
static dGeomID          torso3_geom[N_BODIES];
static dGeomID          head_geom[N_BODIES];
static dGeomID          leftarm1_geom[N_BODIES];
static dGeomID          leftarm2_geom[N_BODIES];
static dGeomID          rightarm1_geom[N_BODIES];
static dGeomID          rightarm2_geom[N_BODIES];
static dGeomID          leftleg1_geom[N_BODIES];
static dGeomID          leftleg2_geom[N_BODIES];
static dGeomID          rightleg1_geom[N_BODIES];
static dGeomID          rightleg2_geom[N_BODIES];
static dGeomID          lefthand_geom[N_BODIES];
static dGeomID          righthand_geom[N_BODIES];
static dGeomID          rightlead_target_geom[N_BODIES];
static dGeomID          leftfollow_target_geom[N_BODIES];


// Makes all the joints of one manikin into a single unit makes an array of them
static dJointGroupID    ragdoll_joints[N_BODIES];


// Names joint constraints
static dJointID         rib1[N_BODIES];
static dJointID         rib2[N_BODIES];
static dJointID         neck[N_BODIES];
static dJointID         leftsholder[N_BODIES];
static dJointID         rightsholder[N_BODIES];
static dJointID         leftelbow[N_BODIES];
static dJointID         rightelbow[N_BODIES];
static dJointID         lefthip[N_BODIES];
static dJointID         righthip[N_BODIES];
static dJointID         leftknee[N_BODIES];
static dJointID         rightknee[N_BODIES];
static dJointID         leftwrist[N_BODIES];
static dJointID         rightwrist[N_BODIES];
static dJointID         follow_back[N_BODIES];
static dJointID         lead_sholder[N_BODIES];


// Rendering parameters.
int                     viewport[] =            { 0, 0, 800, 600 };


// Trackball parameters.
float                   trackBallDiameter       (800.0);


gmtl::Vec3f             currentPosition;
gmtl::Vec3f             lastPosition;


gmtl::Matrix44f         gmtlNavigationMatrix;
gmtl::Matrix44f         trueWorldMatrix; 


bool                    useMouseLeftButton      (false);
bool                    useMouseMiddleButton    (false);
bool                    useMouseRightButton     (false);


enum                    InteractioMode
                        {
                            PICK        = 1,
                            NAVIGATE    = 2
                        };


InteractioMode          mode(PICK);

snx::SoundHandle        bgSoundHandle;
snx::SoundHandle        moveSoundHandle;
snx::SoundHandle        blastSoundHandle;

                        
GLuint loadTexture(std::string fileName)
{
	int extind = fileName.rfind('.');
	std::string ext(&(fileName.c_str()[extind+1]));

	TgaImage *tgaimage = 0;

	int width, height;
	void *pixels;

	tgaimage = new TgaImage(fileName);

	width = tgaimage->getWidth();
	height = tgaimage->getHeight();
	pixels = tgaimage->getPixels();	

	std::cout << "Texture filename is: " << fileName << " width: " << width << " height: " << height << std::endl;

	GLuint index;
	glGenTextures(1,  &index);
	glBindTexture(GL_TEXTURE_2D, index);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if(tgaimage)
		delete tgaimage;

	return index;
}


//does not do anything yet, am hopeing I wouln't need it
void draw_stairs()
{
    glDisable(GL_LIGHTING);  
    glColor3f(1.0, 1.0, 0.8);
    glEnable(GL_TEXTURE_2D); 
    glBindTexture(GL_TEXTURE_2D, glTexIndex);

    glPushMatrix();
    glBegin(GL_QUADS);
        glNormal3f(0.0, 1.0, 0.0);
        glTexCoord3f(0.0, 0.0, 0.0);
        glVertex3f(-2.0, 5.0, 0.0);
        glTexCoord3f(1.0, 0.0, 0.0);
        glVertex3f( 0.0, 5.0, 0.0);
        glTexCoord3f(1.0, 0.0, 1.0);
        glVertex3f( 0.0, 5.0, .5);
        glTexCoord3f(0.0, 0.0, 1.0);
        glVertex3f(-2.0, 5.0, .5);
    glEnd();
    glPopMatrix();
}


void draw()
{
	glDisable(GL_LIGHTING);
	glColor3f(1.0, 1.0, 0.8);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, glTexIndex);

	glPushMatrix();
	glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord3f(0.0, 0.0, 0.0);
		glVertex3f(-10.0, -10.0, 0.0);
		glTexCoord3f(20.0, 0.0, 0.0);
		glVertex3f( 20.0, -10.0, 0.0);
		glTexCoord3f(20.0, 20.0, 0.0);
		glVertex3f( 20.0, 10.0, 0.0);
		glTexCoord3f(0.0, 20.0, 0.0);
		glVertex3f(-10.0, 10.0, 0.0);
	glEnd();
	glPopMatrix();

	//glDisable(GL_TEXTURE_2D);
	//glEnable(GL_LIGHTING);

	dsDrawBox(dGeomGetPosition(stair1), dGeomGetRotation(stair1), sides1);
	dsDrawBox(dGeomGetPosition(stair2), dGeomGetRotation(stair2), sides1);
	dsDrawBox(dGeomGetPosition(stair3), dGeomGetRotation(stair3), sides2);
	dsDrawBox(dGeomGetPosition(stair4), dGeomGetRotation(stair4), sides2);
	dsDrawBox(dGeomGetPosition(stair5), dGeomGetRotation(stair5), sides3);
	dsDrawBox(dGeomGetPosition(stair6), dGeomGetRotation(stair6), sides3);
	dsDrawBox(dGeomGetPosition(stair7), dGeomGetRotation(stair7), sides4);

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);

	dsSetColor (0.9, 0.6, 0.4);
	
	for (int b = 0; b < N_BODIES; b ++)
	{
		if (clicked == b)
			dsSetColor (0, 0, 1);

		glPushMatrix();
		dsDrawCapsule (dGeomGetPosition(torso1_geom[b]),dGeomGetRotation(torso1_geom[b]),.1,.1);

	  	dsDrawSphere (dGeomGetPosition(torso2_geom[b]),dGeomGetRotation(torso2_geom[b]),.1);
	  	dsDrawSphere (dGeomGetPosition(torso3_geom[b]),dGeomGetRotation(torso3_geom[b]),.1);
	  	dsDrawSphere (dGeomGetPosition(head_geom[b]),dGeomGetRotation(head_geom[b]),.075);

	  	dsDrawCapsule (dGeomGetPosition(leftarm1_geom[b]),dGeomGetRotation(leftarm1_geom[b]),.3,.05);
	  	dsDrawCapsule (dGeomGetPosition(leftarm2_geom[b]),dGeomGetRotation(leftarm2_geom[b]),.3,.05);

	  	dsDrawCapsule (dGeomGetPosition(rightarm1_geom[b]),dGeomGetRotation(rightarm1_geom[b]),.3,.05);
	  	dsDrawCapsule (dGeomGetPosition(rightarm2_geom[b]),dGeomGetRotation(rightarm2_geom[b]),.3,.05);

	  	dsDrawCapsule (dGeomGetPosition(leftleg1_geom[b]),dGeomGetRotation(leftleg1_geom[b]),.4,.05);
	  	dsDrawCapsule (dGeomGetPosition(leftleg2_geom[b]),dGeomGetRotation(leftleg2_geom[b]),.4,.05);

	  	dsDrawCapsule (dGeomGetPosition(rightleg1_geom[b]),dGeomGetRotation(rightleg1_geom[b]),.4,.05);
	  	dsDrawCapsule (dGeomGetPosition(rightleg2_geom[b]),dGeomGetRotation(rightleg2_geom[b]),.4,.05);

        glPopMatrix();

        if (clicked == b)
        {
		    dsSetColor (0.9, 0.6, 0.4);
        }
    }
}



// Creates tempotary jiont constraints for coliding objects
static void cb_near_collision(void *data, dGeomID o1, dGeomID o2)
{
	dBodyID		b1 = dGeomGetBody (o1);
	dBodyID		b2 = dGeomGetBody (o2);
	dContact	contact;

    // Exit without doing anything if the two bodies are static
	if(b1 == 0 && b2 == 0)
    {
	    return;
    }

    // Exit without doing anything if the two bodies are connected by a joint
	if(b1 && b2 && dAreConnected (b1, b2))
	{
		/* MTRAP; */
		return;
	}

	contact.surface.mode = 0;
    // Static friction I belive);
	contact.surface.mu = 10;


	if (dCollide (o1, o2, 1, &contact.geom, sizeof (dContactGeom)))
	{
		dJointID c = dJointCreateContact (dyn_world.id(), coll_contacts.id (), &contact);
		dJointAttach (c, b1, b2);
	}
}



void Friction()
{
    // This is a switch for turning on or off the friction (1 = on, 0 = off)
    if (friction == true)  /* [ */
    {
	    // Basic aproximation for kenetic air and ground friction 
	    for (int b = 0; b < N_BODIES; b ++)
	    {
	        // Linear slowing due to air friction
	        dReal       s = 1-0.001*1000/density;

	        // Angular slowing due to air friction
            dReal       t = 1-0.002*1000/density;

	        // Linear slowing due to ground frinction
	        dReal       u = 1-0.01*density/1000;

            //////////////////////////////---torso---/////////////////////////////////////////

	        const dReal	*vel_torso1 = dBodyGetLinearVel (torso1[b]),
		                *rot_torso1 = dBodyGetAngularVel (torso1[b]),
		                *hight_torso1 = dBodyGetPosition (torso1[b]);

		    if (hight_torso1[2] > 0.6)
		    {
			    dBodySetLinearVel (torso1[b], s*vel_torso1[0],s*vel_torso1[1],s*vel_torso1[2]);
			    dBodySetAngularVel (torso1[b],t*rot_torso1[0],t*rot_torso1[1],t*rot_torso1[2]);
		    }
		    else
		    {
			    dBodySetLinearVel (torso1[b], (s+u-1)*vel_torso1[0],(s+u-1)*vel_torso1[1],(s+u-1)*vel_torso1[2]);
			    dBodySetAngularVel (torso1[b],t*rot_torso1[0],t*rot_torso1[1],t*rot_torso1[2]);
		    }

	        const dReal	*vel_torso2 = dBodyGetLinearVel (torso2[b]),
		                *rot_torso2 = dBodyGetAngularVel (torso2[b]),
		                *hight_torso2 = dBodyGetPosition (torso2[b]);

		    if (hight_torso2[2] > 0.6)
		    {
			    dBodySetLinearVel (torso2[b], s*vel_torso2[0],s*vel_torso2[1],s*vel_torso2[2]);
			    dBodySetAngularVel (torso2[b],t*rot_torso2[0],t*rot_torso2[1],t*rot_torso2[2]);
		    }
		    else
		    {
			    dBodySetLinearVel (torso2[b], (s+u-1)*vel_torso2[0],(s+u-1)*vel_torso2[1],(s+u-1)*vel_torso2[2]);
			    dBodySetAngularVel (torso2[b],t*rot_torso2[0],t*rot_torso2[1],t*rot_torso2[2]);
		    }

	        const dReal	*vel_torso3 = dBodyGetLinearVel (torso3[b]),
		                *rot_torso3 = dBodyGetAngularVel (torso3[b]),
		                *hight_torso3 = dBodyGetPosition (torso3[b]);

		    if (hight_torso3[2] > 0.6)
		    {
			    dBodySetLinearVel (torso3[b], s*vel_torso3[0],s*vel_torso3[1],s*vel_torso3[2]);
			    dBodySetAngularVel (torso3[b],t*rot_torso3[0],t*rot_torso3[1],t*rot_torso3[2]);
		    }
		    else
		    {
			    dBodySetLinearVel (torso3[b], (s+u-1)*vel_torso3[0],(s+u-1)*vel_torso3[1],(s+u-1)*vel_torso3[2]);
			    dBodySetAngularVel (torso3[b],t*rot_torso3[0],t*rot_torso3[1],t*rot_torso3[2]);
		    }

            //////////////////////////////---leftarm---//////////////////////////////////////////

	        const dReal	*vel_leftarm1 = dBodyGetLinearVel (leftarm1[b]), 
                        *rot_leftarm1 = dBodyGetAngularVel (leftarm1[b]),
                        *hight_leftarm1 = dBodyGetPosition (leftarm1[b]) ;

	        if (hight_leftarm1[2] > 0.3)
	        {
			    dBodySetLinearVel (leftarm1[b], s*vel_leftarm1[0],s*vel_leftarm1[1],s*vel_leftarm1[2]);
			    dBodySetAngularVel (leftarm1[b],t*rot_leftarm1[0],t*rot_leftarm1[1],t*rot_leftarm1[2]);
		    }
		    else
		    {
			    dBodySetLinearVel (leftarm1[b], (s+u-1)*vel_leftarm1[0],(s+u-1)*vel_leftarm1[1],(s+u-1)*vel_leftarm1[2]);
			    dBodySetAngularVel (leftarm1[b],t*rot_leftarm1[0],t*rot_leftarm1[1],t*rot_leftarm1[2]);
		    }

	        const dReal *vel_leftarm2 = dBodyGetLinearVel (leftarm2[b]),
		                *rot_leftarm2 = dBodyGetAngularVel (leftarm2[b]),
		                *hight_leftarm2 = dBodyGetPosition (leftarm2[b]);

		    if (hight_leftarm2[2] > 0.3)
		    {
			    dBodySetLinearVel (leftarm2[b], s*vel_leftarm2[0],s*vel_leftarm2[1],s*vel_leftarm2[2]);
			    dBodySetAngularVel (leftarm2[b],t*rot_leftarm2[0],t*rot_leftarm2[1],t*rot_leftarm2[2]);
		    }
		    else
		    {
			    dBodySetLinearVel (leftarm2[b], (s+u-1)*vel_leftarm2[0],(s+u-1)*vel_leftarm2[1],(s+u-1)*vel_leftarm2[2]);
			    dBodySetAngularVel (leftarm2[b],t*rot_leftarm2[0],t*rot_leftarm2[1],t*rot_leftarm2[2]);
		    }

            /////////////////////////////---rightarm---/////////////////////////////////////////////////

	        const dReal *vel_rightarm1 = dBodyGetLinearVel (rightarm1[b]),
		                *rot_rightarm1 = dBodyGetAngularVel (rightarm1[b]),
		                *hight_rightarm1 = dBodyGetPosition (rightarm1[b]);
		    if (hight_rightarm1[2] > 0.3)
		    {
			    dBodySetLinearVel (rightarm1[b], s*vel_rightarm1[0],s*vel_rightarm1[1],s*vel_rightarm1[2]);
			    dBodySetAngularVel (rightarm1[b],t*rot_rightarm1[0],t*rot_rightarm1[1],t*rot_rightarm1[2]);
		    }
		    else
		    {
			    dBodySetLinearVel (rightarm1[b], (s+u-1)*vel_rightarm1[0],(s+u-1)*vel_rightarm1[1],(s+u-1)*vel_rightarm1[2]);
			    dBodySetAngularVel (rightarm1[b],t*rot_rightarm1[0],t*rot_rightarm1[1],t*rot_rightarm1[2]);
		    }

	        const dReal	*vel_rightarm2 = dBodyGetLinearVel (rightarm2[b]),
		                *rot_rightarm2 = dBodyGetAngularVel (rightarm2[b]),
		                *hight_rightarm2 = dBodyGetPosition (rightarm2[b]);

		    if (hight_rightarm2[2] > 0.3)
		    {
			    dBodySetLinearVel (rightarm2[b], s*vel_rightarm2[0],s*vel_rightarm2[1],s*vel_rightarm2[2]);
			    dBodySetAngularVel (rightarm2[b],t*rot_rightarm2[0],t*rot_rightarm2[1],t*rot_rightarm2[2]);
		    }
		    else
		    {
			    dBodySetLinearVel (rightarm2[b], (s+u-1)*vel_rightarm2[0],(s+u-1)*vel_rightarm2[1],(s+u-1)*vel_rightarm2[2]);
			    dBodySetAngularVel (rightarm2[b],t*rot_rightarm2[0],t*rot_rightarm2[1],t*rot_rightarm2[2]);
		    }

            ////////////////////////////---leftleg---////////////////////////////////////////////////////

	        const dReal	*vel_leftleg1 = dBodyGetLinearVel (leftleg1[b]),
		                *rot_leftleg1 = dBodyGetAngularVel (leftleg1[b]),
		                *hight_leftleg1 = dBodyGetPosition (leftleg1[b]);

            if (hight_leftleg1[2] > 0.3)
		    {
			    dBodySetLinearVel (leftleg1[b], s*vel_leftleg1[0],s*vel_leftleg1[1],s*vel_leftleg1[2]);
			    dBodySetAngularVel (leftleg1[b],t*rot_leftleg1[0],t*rot_leftleg1[1],t*rot_leftleg1[2]);
		    }
		    else
		    {
			    dBodySetLinearVel (leftleg1[b], (s+u-1)*vel_leftleg1[0],(s+u-1)*vel_leftleg1[1],(s+u-1)*vel_leftleg1[2]);
			    dBodySetAngularVel (leftleg1[b],t*rot_leftleg1[0],t*rot_leftleg1[1],t*rot_leftleg1[2]);
		    }

	        const dReal	*vel_leftleg2 = dBodyGetLinearVel (leftleg2[b]),
		                *rot_leftleg2 = dBodyGetAngularVel (leftleg2[b]),
		                *hight_leftleg2 = dBodyGetPosition (leftleg2[b]); 

		    if (hight_leftleg2[2] > 0.3)
		    {
			    dBodySetLinearVel (leftleg2[b], s*vel_leftleg2[0],s*vel_leftleg2[1],s*vel_leftleg2[2]);
			    dBodySetAngularVel (leftleg2[b],t*rot_leftleg2[0],t*rot_leftleg2[1],t*rot_leftleg2[2]);
		    }
		    else
		    {
			    dBodySetLinearVel (leftleg2[b], (s+u-1)*vel_leftleg2[0],(s+u-1)*vel_leftleg2[1],(s+u-1)*vel_leftleg2[2]);
			    dBodySetAngularVel (leftleg2[b],t*rot_leftleg2[0],t*rot_leftleg2[1],t*rot_leftleg2[2]);
		    }

            ////////////////////////////---rightleg---///////////////////////////////////////////////////////

	        const dReal	*vel_rightleg1 = dBodyGetLinearVel (rightleg1[b]),
		                *rot_rightleg1 = dBodyGetAngularVel (rightleg1[b]),
		                *hight_rightleg1 = dBodyGetPosition (rightleg1[b]);

		    if (hight_rightleg1[2] > 0.3)
		    {
			    dBodySetLinearVel (rightleg1[b], s*vel_rightleg1[0],s*vel_rightleg1[1],s*vel_rightleg1[2]);
			    dBodySetAngularVel (rightleg1[b],t*rot_rightleg1[0],t*rot_rightleg1[1],t*rot_rightleg1[2]);
		    }
		    else
		    {
			    dBodySetLinearVel (rightleg1[b], (s+u-1)*vel_rightleg1[0],(s+u-1)*vel_rightleg1[1],(s+u-1)*vel_rightleg1[2]);
			    dBodySetAngularVel (rightleg1[b],t*rot_rightleg1[0],t*rot_rightleg1[1],t*rot_rightleg1[2]);
		    }

	        const dReal	*vel_rightleg2 = dBodyGetLinearVel (rightleg2[b]),
		                *rot_rightleg2 = dBodyGetAngularVel (rightleg2[b]),
		                *hight_rightleg2 = dBodyGetPosition (rightleg2[b]);

            if (hight_rightleg2[2] > 0.3)
		    {
			    dBodySetLinearVel (rightleg2[b], s*vel_rightleg2[0],s*vel_rightleg2[1],s*vel_rightleg2[2]);
			    dBodySetAngularVel (rightleg2[b],t*rot_rightleg2[0],t*rot_rightleg2[1],t*rot_rightleg2[2]);
		    }
		    else
		    {
			    dBodySetLinearVel (rightleg2[b], (s+u-1)*vel_rightleg2[0],(s+u-1)*vel_rightleg2[1],(s+u-1)*vel_rightleg2[2]);
			    dBodySetAngularVel (rightleg2[b],t*rot_rightleg2[0],t*rot_rightleg2[1],t*rot_rightleg2[2]);
		    }
        }
    }
}


// Sets up interactivity
void interact()
{
	glSelectBuffer(BUFSIZE,selectBuf);
	glRenderMode(GL_SELECT);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glGetIntegerv(GL_VIEWPORT, viewport);
	glLoadIdentity();
	gluPickMatrix(cursorX, viewport[3]-cursorY, 1, 1, viewport);
	gluPerspective(60.0, (double)viewport[2]/viewport[3], 0.1, 10000.0);
	glMatrixMode(GL_MODELVIEW);
	glInitNames();
}

void movedoll()
{
	int bodynum = name%N_BODIES;
	int bodypart = name/N_BODIES;
	name = -N_BODIES;
	dReal z= 0.0;
	int scalar = 10;
	clicked = -1;

    gmtl::Matrix44f temp;
    gmtl::Vec3f direction, result;
    direction.set((cursorX2-cursorX)*1.0, (cursorY-cursorY2)*1.0, z);

    gmtl::invert(temp, trueWorldMatrix);
    gmtl::xform(result, temp, direction);

	switch (bodypart)
	{
		case -1:
			std::cout<<"nothing has been grabbed\n";
			break;
		case 0:
			dBodySetLinearVel(torso1[bodynum], result[0]*scalar,  result[1]*scalar, result[2]);
			break;
		case 1:
			dBodySetLinearVel(torso2[bodynum], result[0]*scalar,  result[1]*scalar, result[2]);
			break;
		case 2:
			dBodySetLinearVel(torso3[bodynum], result[0]*scalar,  result[1]*scalar, result[2]);
			break;
		case 3:
			dBodySetLinearVel(head[bodynum], result[0]*scalar,  result[1]*scalar, result[2]);
			break;
		case 4:
			dBodySetLinearVel(leftarm1[bodynum], result[0]*scalar,  result[1]*scalar, result[2]);
			break;
		case 5:
			dBodySetLinearVel(leftarm2[bodynum], result[0]*scalar,  result[1]*scalar, result[2]);
			break;
		case 6:
			dBodySetLinearVel(rightarm1[bodynum], result[0]*scalar,  result[1]*scalar, result[2]);
			break;
		case 7:
			dBodySetLinearVel(rightarm2[bodynum], result[0]*scalar,  result[1]*scalar, result[2]);
			break;
		case 8:
			dBodySetLinearVel(leftleg1[bodynum], result[0]*scalar,  result[1]*scalar, result[2]);
			break;
		case 9:
			dBodySetLinearVel(leftleg2[bodynum], result[0]*scalar,  result[1]*scalar, result[2]);
			break;
		case 10:
			dBodySetLinearVel(rightleg1[bodynum], result[0]*scalar,  result[1]*scalar, result[2]);
			break;
		case 11:
			dBodySetLinearVel(rightleg2[bodynum], result[0]*scalar,  result[1]*scalar, result[2]);
			break;
	}
}


// Grabs information from mouse interacting with manikins and sends the name/number of the object clicked on to movedoll()
void processHits (GLuint buffer[])
{
	if (hits!=0)
	{
		std::cout<<"# of hits "<<hits<<'\n';
		GLuint smallest = 4294967295;
		for (int i=1; i < hits*4; i+= 4)
		{
			if (buffer[i]<=smallest)
			{
				smallest = buffer[i];
				name = buffer[i+2];
			}
		}
		clicked = name%N_BODIES;
	}
}



void endinteract()
{
	// Restoring the original projection matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glFlush();

	// Returning to normal rendering mode
	hits = glRenderMode(GL_RENDER);

	if(hits!=0)
	{
		processHits(selectBuf);
	}
}



void InteractiveRender ()
{
	for(int b = 0; b < N_BODIES; b ++)
	{
	    glInitNames();
	    glPushName(b);

	    dsDrawCapsule (dGeomGetPosition(torso1_geom[b]),dGeomGetRotation(torso1_geom[b]),.1,.1);
	    glLoadName(b+N_BODIES);
	    dsDrawSphere (dGeomGetPosition(torso2_geom[b]),dGeomGetRotation(torso2_geom[b]),.1);
	    glLoadName(b+N_BODIES*2);
	    dsDrawSphere (dGeomGetPosition(torso3_geom[b]),dGeomGetRotation(torso3_geom[b]),.1);

	    glLoadName(b+N_BODIES*3);
	    dsDrawSphere (dGeomGetPosition(head_geom[b]),dGeomGetRotation(head_geom[b]),.075);

	    glLoadName(b+N_BODIES*4);
	    dsDrawCapsule (dGeomGetPosition(leftarm1_geom[b]),dGeomGetRotation(leftarm1_geom[b]),.3,.05);
	    glLoadName(b+N_BODIES*5);
	    dsDrawCapsule (dGeomGetPosition(leftarm2_geom[b]),dGeomGetRotation(leftarm2_geom[b]),.3,.05);

	    glLoadName(b+N_BODIES*6);
	    dsDrawCapsule (dGeomGetPosition(rightarm1_geom[b]),dGeomGetRotation(rightarm1_geom[b]),.3,.05);
	    glLoadName(b+N_BODIES*7);
	    dsDrawCapsule (dGeomGetPosition(rightarm2_geom[b]),dGeomGetRotation(rightarm2_geom[b]),.3,.05);

	    glLoadName(b+N_BODIES*8);
	    dsDrawCapsule (dGeomGetPosition(leftleg1_geom[b]),dGeomGetRotation(leftleg1_geom[b]),.4,.05);
	    glLoadName(b+N_BODIES*9);
	    dsDrawCapsule (dGeomGetPosition(leftleg2_geom[b]),dGeomGetRotation(leftleg2_geom[b]),.4,.05);

	    glLoadName(b+N_BODIES*10);
	    dsDrawCapsule (dGeomGetPosition(rightleg1_geom[b]),dGeomGetRotation(rightleg1_geom[b]),.4,.05);
	    glLoadName(b+N_BODIES*11);
	    dsDrawCapsule (dGeomGetPosition(rightleg2_geom[b]),dGeomGetRotation(rightleg2_geom[b]),.4,.05);
	    glPopName();
	}
}


// Updates program at each time step
static void cb_sim_step()
{
	const int n = 10;
	for (int i = 0; i < n; i ++)
	{
		dSpaceCollide (coll_space_id, 0, &cb_near_collision);
		dyn_world.step (dReal(TIME_STEP/n));
		coll_contacts.empty ();
	}

	Friction();
}


// Set and initialize sound related items. 
void initSound()
{
    // Hardcoded as of now. 
    std::string api("OpenAL"); 
    std::string background(".//data/sounds/background.wav");
    std::string blast(".//data/sounds/blast.wav");
    std::string move(".//data/sounds/move.wav");    
        
   /* if(!snxFileIO::fileExists(background.c_str() ||
       !snxFileIO::fileExists(blast.c_str()) ||
       !snxFileIO::fileExists(move.c_str()) 
      );
    {
        std::cerr << "ERROR: Sounds file not found error: " << std::endl;
        return; 
    }*/

    // Create sound info objects. 
    snx::SoundInfo bgSoundInfo; 
    bgSoundInfo.filename    = background; 
    bgSoundInfo.datasource  = snx::SoundInfo::FILESYSTEM;        

    bgSoundHandle.init(" Background sound: ");
    bgSoundHandle.configure(bgSoundInfo);    

    // start sonix using OpenAL
    snx::sonix::instance()->changeAPI( api );
}


// Sets initial parameters
void init()
{
	int b;

	dInitODE2(0);

	// Let bodies move into each other a bit.
	dReal  cf_mixing;// = 1 / TIME_STEP * K_SPRING + K_DAMP;
	dReal  err_reduct;// = TIME_STEP * K_SPRING * cf_mixing;
	err_reduct = REAL(0.5);
	cf_mixing = REAL(0.001);
	dWorldSetERP (dyn_world.id (), err_reduct);
	dWorldSetCFM (dyn_world.id (), cf_mixing);


	// Set the gravity for the system.
	dyn_world.setGravity (0, 0.0, -980);

	// Allow things to collide.
	coll_space_id = dSimpleSpaceCreate (0);


	///////////////////////////////////////////////////////////////////////
	// Collision geoms and joints
	//
	
	// Floor
	dCreatePlane (coll_space_id, 0, 0, 1, 0);

	// Stairs
	stair1 = dCreateBox   (coll_space_id, 2, 1, 0.5);
	stair2 = dCreateBox   (coll_space_id, 2, 1, 0.5);
	stair3 = dCreateBox   (coll_space_id, 2, 1, 1);
	stair4 = dCreateBox   (coll_space_id, 2, 1, 1);
	stair5 = dCreateBox   (coll_space_id, 2, 1, 1.5);
	stair6 = dCreateBox   (coll_space_id, 2, 1, 1.5);
	stair7 = dCreateBox   (coll_space_id, 12, 2, 2);


	dGeomSetPosition (stair1, -1, 5.5, 0.25);
	dGeomSetPosition (stair2, 9, 5.5, 0.25);
	dGeomSetPosition (stair3, -1, 6.5, 0.5);
	dGeomSetPosition (stair4, 9, 6.5, 0.5);
	dGeomSetPosition (stair5, -1, 7.5, 0.75);
	dGeomSetPosition (stair6, 9, 7.5, 0.75);
	dGeomSetPosition (stair7, 4, 9, 1);

	//Four walls
	dCreatePlane (coll_space_id,  1, 0, 0, 0);
	dCreatePlane (coll_space_id, -1, 0, 0, -STAGE_SIZE);
	dCreatePlane (coll_space_id,  0,  1, 0, 0);
	dCreatePlane (coll_space_id,  0, -1, 0, -STAGE_SIZE);

	coll_contacts.create (0);

	for (b = 0; b < N_BODIES; b ++)
	{
		int     l = (int) (1 + sqrt ((double) N_BODIES));
		dReal  x = dReal((0.5 + (b / l)) / l * STAGE_SIZE);
		dReal  y = dReal((0.5 + (b % l)) / l * STAGE_SIZE);
		dReal  z = REAL(1.2);


		// Center of mass hight (torso2)
		dReal z1 = z;

		// Head hight
		dReal zhead = z+ 0.375;

		// Neck hight
		dReal zneck = z+ 0.3;

		// Sholder hight
		dReal zsholder = z+ 0.25;

		// Elbow hight
		dReal zelbow = z+ 0.55;

		// Hip hight
		dReal zhip = z- 0.2;

		// Knee hight
		dReal zknee = z- 0.6;

		// Center of body
		dReal x1 = x;

		// Left sholder/hip position
		dReal x2 = x+ 0.1;

		// Right sholder/hip position
		dReal x3 = x- 0.1;


    // Creates objects and assigns names
		torso1[b] = dBodyCreate(dyn_world);
		torso2[b] = dBodyCreate(dyn_world);
		torso3[b] = dBodyCreate(dyn_world);
		head[b] = dBodyCreate(dyn_world);
		leftarm1[b] = dBodyCreate(dyn_world);
		leftarm2[b] = dBodyCreate(dyn_world);
		rightarm1[b] = dBodyCreate(dyn_world);
		rightarm2[b] = dBodyCreate(dyn_world);
		leftleg1[b] = dBodyCreate(dyn_world);
		leftleg2[b] = dBodyCreate(dyn_world);
		rightleg1[b] = dBodyCreate(dyn_world);
		rightleg2[b] = dBodyCreate(dyn_world);
//        lefthand[b] = dBodyCreate(dyn_world);
//        righthand[b] = dBodyCreate(dyn_world);
//        rightlead_target[b] = dBodyCreate(dyn_world);
//        leftfollow_target[b] = dBodyCreate(dyn_world);


    // Creates shapes and assigns names and bodies
		torso1_geom[b] = dCreateCCylinder (coll_space_id, 0.1, 0.1);
		dGeomSetBody (torso1_geom[b], torso1[b]);
		torso2_geom[b] = dCreateSphere (coll_space_id, 0.1);
		dGeomSetBody (torso2_geom[b], torso2[b]);
		torso3_geom[b] = dCreateSphere (coll_space_id, 0.1);
		dGeomSetBody (torso3_geom[b], torso3[b]);

		head_geom[b] = dCreateSphere (coll_space_id, 0.075);
		dGeomSetBody (head_geom[b], head[b]);

		leftarm1_geom[b] = dCreateCCylinder (coll_space_id, 0.05, 0.3);
		dGeomSetBody (leftarm1_geom[b], leftarm1[b]);
		leftarm2_geom[b] = dCreateCCylinder (coll_space_id, 0.05, 0.3);
		dGeomSetBody (leftarm2_geom[b], leftarm2[b]);

		rightarm1_geom[b] = dCreateCCylinder (coll_space_id, 0.05, 0.3);
		dGeomSetBody (rightarm1_geom[b], rightarm1[b]);
		rightarm2_geom[b] = dCreateCCylinder (coll_space_id, 0.05, 0.3);
		dGeomSetBody (rightarm2_geom[b], rightarm2[b]);

		leftleg1_geom[b] = dCreateCCylinder (coll_space_id, 0.05, 0.4);
		dGeomSetBody (leftleg1_geom[b], leftleg1[b]);
		leftleg2_geom[b] = dCreateCCylinder (coll_space_id, 0.05, 0.4);
		dGeomSetBody (leftleg2_geom[b], leftleg2[b]);

		rightleg1_geom[b] = dCreateCCylinder (coll_space_id, 0.05, 0.4);
		dGeomSetBody (rightleg1_geom[b], rightleg1[b]);
		rightleg2_geom[b] = dCreateCCylinder (coll_space_id, 0.05, 0.4);
		dGeomSetBody (rightleg2_geom[b], rightleg2[b]);
/*
        lefthand_geom[b] = dCreateSphere (0, 0.0001);
        dGeomSetBody (lefthand_geom[b], lefthand[b]);
        righthand_geom[b] = dCreateSphere (0, 0.0001);
        dGeomSetBody (righthand_geom[b], righthand[b]);
        rightlead_target_geom[b] = dCreateSphere (0, 0.0001);
        dGeomSetBody (rightlead_target_geom[b], rightlead_target[b]);
        leftfollow_target_geom[b] = dCreateSphere (0, 0.0001);
        dGeomSetBody (leftfollow_target_geom[b], leftfollow_target[b]);
*/
		// Positions bodies/shapes
		dGeomSetPosition(torso1_geom[b], x1, y, z1+.2);
		dGeomSetPosition(torso2_geom[b], x1, y, z1);
		dGeomSetPosition(torso3_geom[b], x1, y, z1-.15);
		dGeomSetPosition(head_geom[b], x1, y, zhead);
		dGeomSetPosition(leftarm1_geom[b], x2, y, zsholder + .15);
		dGeomSetPosition(leftarm2_geom[b], x2, y, zsholder + .45);
		dGeomSetPosition(rightarm1_geom[b], x3, y, zsholder + .15);
		dGeomSetPosition(rightarm2_geom[b], x3, y, zsholder + .45);
		dGeomSetPosition(leftleg1_geom[b], x2, y, zhip - .2);
		dGeomSetPosition(leftleg2_geom[b], x2, y, zhip - .6);
		dGeomSetPosition(rightleg1_geom[b], x3, y, zhip - .2);
		dGeomSetPosition(rightleg2_geom[b], x3, y, zhip - .6);
//        dBodySetPosition(lefthand[b], x2, y, zsholder + .625);
//        dBodySetPosition(righthand[b], x3, y, zsholder + .625);
//        dBodySetPosition(rightlead_target[b], x1, y + 0.1, z1);
//        dBodySetPosition(leftfollow_target[b], x3, y, zsholder);


		// Makes things oriented up
		dMatrix3 dir = {1,1,1,1,1,1,1,1,1,1,1,1};
		dGeomSetRotation(torso1_geom[b], dir);
		dGeomSetRotation(torso2_geom[b], dir);
		dGeomSetRotation(torso3_geom[b], dir);
		dGeomSetRotation(head_geom[b], dir);
		dGeomSetRotation(leftarm1_geom[b],dir);
		dGeomSetRotation(leftarm2_geom[b],dir);
		dGeomSetRotation(rightarm1_geom[b],dir);
		dGeomSetRotation(rightarm2_geom[b],dir);
		dGeomSetRotation(leftleg1_geom[b], dir);
		dGeomSetRotation(leftleg2_geom[b], dir);
		dGeomSetRotation(rightleg1_geom[b],dir);
		dGeomSetRotation(rightleg2_geom[b],dir);
//        dBodySetRotation(lefthand[b],dir);
//        dBodySetRotation(righthand[b],dir);
//        dBodySetRotation(rightlead_target[b],dir);
//        dBodySetRotation(leftfollow_target[b],dir);


		// Makes a group for the joints to join
		ragdoll_joints[b] = dJointGroupCreate (0);


		// Makes, assigns a name to, attaches, and places joints

		rib1[b] = dJointCreateBall (dyn_world.id (), ragdoll_joints[b]);
		dJointAttach (rib1[b], torso1[b], torso2[b]);
		dJointSetBallAnchor (rib1[b], x1, y, z+ 0.1);

		rib2[b] = dJointCreateBall (dyn_world.id (), ragdoll_joints[b]);
		dJointAttach (rib2[b], torso2[b], torso3[b]);
		dJointSetBallAnchor (rib2[b], x1, y, z- 0.1);

		neck[b] = dJointCreateBall (dyn_world.id (), ragdoll_joints[b]);
		dJointAttach (neck[b], head[b], torso1[b]);
		dJointSetBallAnchor (neck[b], x1, y, zneck);

		leftsholder[b] = dJointCreateBall (dyn_world.id (), ragdoll_joints[b]);
		dJointAttach (leftsholder[b], leftarm1[b], torso1[b]);
		dJointSetBallAnchor (leftsholder[b], x2, y, zsholder);

		leftelbow[b] = dJointCreateHinge (dyn_world.id (), ragdoll_joints[b]);
		dJointAttach (leftelbow[b], leftarm1[b], leftarm2[b]);
		dJointSetHingeAnchor (leftelbow[b], x2, y, zelbow);
		dJointSetHingeAxis (leftelbow[b], 1, 0, 0);

		rightsholder[b] = dJointCreateBall (dyn_world.id (), ragdoll_joints[b]);
		dJointAttach (rightsholder[b], rightarm1[b], torso1[b]);
		dJointSetBallAnchor (rightsholder[b], x3, y, zsholder);

		rightelbow[b] = dJointCreateHinge (dyn_world.id (), ragdoll_joints[b]);
		dJointAttach (rightelbow[b], rightarm1[b], rightarm2[b]);
		dJointSetHingeAnchor (rightelbow[b], x3, y, zelbow);
		dJointSetHingeAxis (rightelbow[b], 1, 0, 0);

		lefthip[b] = dJointCreateBall (dyn_world.id (), ragdoll_joints[b]);
		dJointAttach (lefthip[b], leftleg1[b], torso3[b]);
		dJointSetBallAnchor (lefthip[b], x2, y, zhip);

		leftknee[b] = dJointCreateHinge (dyn_world.id (), ragdoll_joints[b]);
		dJointAttach (leftknee[b], leftleg1[b], leftleg2[b]);
		dJointSetHingeAnchor (leftknee[b], x2, y, zknee);
		dJointSetHingeAxis (leftknee[b], 1, 0, 0);

		righthip[b] = dJointCreateBall (dyn_world.id (), ragdoll_joints[b]);
		dJointAttach (righthip[b], rightleg1[b], torso3[b]);
		dJointSetBallAnchor (righthip[b], x3, y, zhip);

		rightknee[b] = dJointCreateHinge (dyn_world.id (), ragdoll_joints[b]);
		dJointAttach (rightknee[b], rightleg1[b], rightleg2[b]);
		dJointSetHingeAnchor (rightknee[b], x3, y, zknee);
		dJointSetHingeAxis (rightknee[b], 1, 0, 0);
/*
        leftwrist[b] = dJointCreateBall (dyn_world.id(), ragdoll_joints[b]);
        dJointAttach (leftwrist[b], leftarm2[b], lefthand[b]);
        dJointSetBallAnchor (leftwrist[b], x2, y, zsholder + .625);

        rightwrist[b] = dJointCreateBall (dyn_world.id(), ragdoll_joints[b]);
        dJointAttach (rightwrist[b], rightarm2[b], righthand[b]);
        dJointSetBallAnchor (rightwrist[b], x3, y, zsholder + .625);

        follow_back[b] = dJointCreateBall (dyn_world.id(), ragdoll_joints[b]);
        dJointAttach (follow_back[b], torso2[b], rightlead_target[b]);
        dJointSetBallAnchor (follow_back[b], x1, y+ 0.1, z1);

        lead_sholder[b] = dJointCreateBall (dyn_world.id(), ragdoll_joints[b]);
        dJointAttach (lead_sholder[b], rightarm1[b], leftfollow_target[b]);
        dJointSetBallAnchor (lead_sholder[b], x3, y, zsholder);
*/

		// Gives mass to manikins
		dMass m;

		// Gives torso1 mass
		dMassSetCappedCylinder (&m, density, 1, REAL(0.05), REAL(0.6));
        dBodySetMass(torso1[b], &m);
		// Gives torso2 mass
		dMassSetSphere (&m, density, REAL(0.1));
        dBodySetMass(torso2[b], &m);

		// Gives torso3 mass
		dMassSetSphere (&m, density, REAL(0.1));
        dBodySetMass(torso3[b], &m);

		// gives head mass
		dMassSetSphere (&m, density, REAL(0.075));
        dBodySetMass(head[b], &m);

		// Gives leftarm1 mass
		dMassSetCappedCylinder (&m, density, 1, REAL(0.05), REAL(0.3));
        dBodySetMass(leftarm1[b], &m);

		// Gives leftarm2 mass
		dMassSetCappedCylinder (&m, density, 1, REAL(0.05), REAL(0.3));
        dBodySetMass(leftarm2[b], &m);

		// Gives rightarm1 mass
		dMassSetCappedCylinder (&m, density, 1, REAL(0.05), REAL(0.3));
        dBodySetMass(rightarm1[b], &m);

		// Gives rightarm2 mass
		dMassSetCappedCylinder (&m, density, 1, REAL(0.05), REAL(0.3));
        dBodySetMass(rightarm2[b], &m);

		// Gives leftleg1 mass
		dMassSetCappedCylinder (&m, density, 1, REAL(0.05), REAL(0.4));
        dBodySetMass(leftleg1[b], &m);

		// Gives leftleg2 mass
		dMassSetCappedCylinder (&m, density, 1, REAL(0.05), REAL(0.4));
        dBodySetMass(leftleg2[b], &m);

		// Gives rightleg1 mass
		dMassSetCappedCylinder (&m, density, 1, REAL(0.05), REAL(0.4));
        dBodySetMass(rightleg1[b], &m);

		// Gives rightleg2 mass
		dMassSetCappedCylinder (&m, density, 1, REAL(0.05), REAL(0.4));
        dBodySetMass(rightleg2[b], &m);
/*
        // Gives lefthand mass
        dMassSetZero (&m);
        dBodySetMass(lefthand[b], &m);

        // Gives righthand mass
        dMassSetZero (&m);
        dBodySetMass(righthand[b], &m);
*/
	}

	// Setup stuff
	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);
	glShadeModel (GL_FLAT);
	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LESS);
	glEnable (GL_CULL_FACE);
	glCullFace (GL_BACK);
	glFrontFace (GL_CCW);

	// Leave openGL in a known state - flat shaded white, no textures
	glEnable (GL_LIGHTING);
	glShadeModel (GL_FLAT);
	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LESS);
	glColor3f (1,1,1);

	glTexIndex = loadTexture("./data/wood.tga");

    // Initialize sound related items. 
    initSound();

    bgSoundHandle.trigger( -1 );     
}

// Helps the manikins remain standing while dancing by applying an upward force and mock body tension
void stand()
{
    for (int b=0; b<N_BODIES; b++)
    {
	    float base = 4.5;
	    int arm_tenser = 5;
	    int leg_tenser = 15;
	    int scale = 35000;
	    dBodyAddForce(head[b], 0, 0, (base+leg_tenser)*scale);
	    dBodyAddForce(leftarm1[b], 0, 0, base*scale);
	    dBodyAddForce(leftarm2[b], 0, 0, (base-arm_tenser)*scale);
	    dBodyAddForce(rightarm1[b], 0, 0, base*scale);
	    dBodyAddForce(rightarm2[b], 0, 0, (base-arm_tenser)*scale);
	    dBodyAddForce(torso1[b], 0, 0, (base+2*arm_tenser)*scale);
	    dBodyAddForce(torso2[b], 0, 0, base*scale);
	    dBodyAddForce(torso3[b], 0, 0, (base+leg_tenser)*scale);
	    dBodyAddForce(leftleg1[b], 0, 0, base*scale);
	    dBodyAddForce(rightleg1[b], 0, 0, base*scale);
	    dBodyAddForce(leftleg2[b], 0, 0, (base-leg_tenser)*scale);
	    dBodyAddForce(rightleg2[b], 0, 0, (base-leg_tenser)*scale);
    }
}

// Causes manikins to move in a two step rhythm
void odd()
{
	for (int b = 0; b < N_BODIES; b+= 2)
	{
		dBodyAddForce(leftleg2[b], 1000/TIME_STEP, 0, 0);
		dBodyAddForce(rightleg2[b], 1000/TIME_STEP, 0, 0);
	}

	for (int b = 1; b < N_BODIES; b+= 2)
	{
		dBodyAddForce(leftleg2[b], 0, 1000/TIME_STEP, 0);
		dBodyAddForce(rightleg2[b], 0, -1000/TIME_STEP, 0);
	}
}

// Causes manikins to move in a two step rhythm
void even()
{
	for (int b = 0; b < N_BODIES; b+= 2)
	{
		dBodyAddForce(leftleg2[b], -1000/TIME_STEP, 0, 0);
		dBodyAddForce(rightleg2[b], -1000/TIME_STEP, 0, 0);
	}

	for (int b = 1; b < N_BODIES; b+= 2)
	{
		dBodyAddForce(leftleg2[b], 0, -1000/TIME_STEP, 0);
		dBodyAddForce(rightleg2[b], 0, 1000/TIME_STEP, 0);
	}
}

// Auto corrects for bad balance and leaning over too far while dancing
void balance()
{
	for (int b = 0; b < N_BODIES; b+= 1)
	{
    const dReal	*torso1pos = dBodyGetPosition (torso1[b]),
		*leftleg2pos = dBodyGetPosition (leftleg2[b]),
		*rightleg2pos = dBodyGetPosition (rightleg2[b]),
		//*leftarm2pos = dBodyGetPosition (leftarm2[b]),
		//*rightarm2pos = dBodyGetPosition (rightarm2[b]),
		*leftleg1pos = dBodyGetPosition (leftleg1[b]),
		*rightleg1pos = dBodyGetPosition (rightleg1[b]),
		//*leftarm1pos = dBodyGetPosition (leftarm1[b]),
		//*rightarm1pos = dBodyGetPosition (rightarm1[b]),
		limbs_x_pos = (leftleg2pos[0] + rightleg2pos[0] + leftleg1pos[0] + rightleg1pos[0])/4,
		limbs_y_pos = (leftleg2pos[1] + rightleg2pos[1] + leftleg1pos[1] + rightleg1pos[1])/4;
		//*torso1dir = dBodyGetQuaternion (torso1[0]),
		//*torso2dir = dBodyGetQuaternion (torso2[0]),
		//*torso3dir = dBodyGetQuaternion (torso3[0]);

    /*
    if (b==0)
	    if (torso2dir[0]-torso1dir[0] > 0.1)
		    dBodyAddTorque (torso1[0], 0, 0, 1000);
	    if (torso1dir[0]-torso2dir[0] > 0.1)
		    dBodyAddTorque (torso1[0], 0, 0, -1000);
    */

		dBodyAddForce(torso1[b], (limbs_x_pos-torso1pos[0])*1000000, 0, 0);
		dBodyAddForce(torso1[b], 0, (limbs_y_pos-torso1pos[1])*1000000, 0);
		dBodyAddForce(leftleg1[b], (limbs_x_pos-torso1pos[0])*-500000, 0, 0);
		dBodyAddForce(leftleg1[b], 0, (limbs_y_pos-torso1pos[1])*-500000, 0);
		dBodyAddForce(rightleg1[b], (limbs_x_pos-torso1pos[0])*-500000, 0, 0);
		dBodyAddForce(rightleg1[b], 0, (limbs_y_pos-torso1pos[1])*-500000, 0);

	  /*
	  //should replace with if floor collide check
	  if (leftleg2pos[2] <= .225)
		{
		  dBodyAddForce(leftleg1[b], 0, 0, 5000000);
		}
	  if (rightleg2pos[2] <= .225)
		{
		  dBodyAddForce(rightleg1[b], 0, 0, 5000000);
		}
	  */
	}
}


// Couses manikins to move in a two step rhythm
void dance(int step)
{
    if (step%4<2)
    {
		odd();
    }
	else
    {
		even();
    }
}


// Waltz dance movement
void first()
{
	for(int b = 0; b < N_BODIES; b++)
	{
		dBodySetLinearVel(rightleg2[b], 0, 0, 0);
		dBodySetForce(leftleg2[b], -500/TIME_STEP, 0, 0);
		dBodyAddForce(torso1[b], -250/TIME_STEP, 0, 0);
	}
}

// Waltz dance movement
void second()
{
	for(int b = 0; b < N_BODIES; b++)
	{
		dBodySetLinearVel(leftleg2[b], 0, 0, 0);
		dBodySetForce(rightleg2[b], -500/TIME_STEP, 0, 0);
		dBodyAddForce(torso3[b], -250/TIME_STEP, 0, 0);
	}
}

// Waltz dance movement
void third()
{
	for(int b = 0; b < N_BODIES; b++)
	{
		dBodySetLinearVel(rightleg2[b], 0, 0, 0);
		dBodySetForce(leftleg2[b], 0, 500/TIME_STEP, 0);
		dBodyAddForce(torso1[b], 0, 250/TIME_STEP, 0);
	}
}

// Waltz dance movement
void fourth()
{
	for(int b = 0; b < N_BODIES; b++)
	{
		dBodySetLinearVel(leftleg2[b], 0, 0, 0);
		dBodySetForce(rightleg2[b], 0, 500/TIME_STEP, 0);
		dBodyAddForce(torso3[b], 0, 250/TIME_STEP, 0);
	}
}

// Waltz dance movement
void fith()
{
	for(int b = 0; b < N_BODIES; b++)
	{
		dBodySetLinearVel(rightleg2[b], 0, 0, 0);
		dBodySetForce(rightleg2[b], 500/TIME_STEP, 0, 0);
		dBodyAddForce(torso3[b], 250/TIME_STEP, 0, 0);
	}
}

// Waltz dance movement
void sixth()
{
	for(int b = 0; b < N_BODIES; b++)
	{
		dBodySetLinearVel(rightleg2[b], 0, 0, 0);
		dBodySetForce(leftleg2[b], 500/TIME_STEP, 0, 0);
		dBodyAddForce(torso1[b], 250/TIME_STEP, 0, 0);
	}
}

// Waltz dance movement
void seventh()
{
	for (int b = 0; b < N_BODIES; b++)
	{
		dBodySetLinearVel(leftleg2[b], 0, 0, 0);
		dBodySetForce(leftleg2[b], 0, -500/TIME_STEP, 0);
		dBodyAddForce(torso3[b], 0, -250/TIME_STEP, 0);
	}
}

// Waltz dance movement
void eigth()
{
	for (int b = 0; b < N_BODIES; b++)
	{
		dBodySetLinearVel(leftleg2[b], 0, 0, 0);
		dBodySetForce(rightleg2[b], 0, -500/TIME_STEP, 0);
		dBodyAddForce(torso1[b], 0, -250/TIME_STEP, 0);
	}
}

// Eight step dance proformed by the manikins
void waltz(int step)
{
	if (step%8==1)
		first();
	else if (step%8==2)
		second();
	else if (step%8==3)
		third();
	else if (step%8==4)
		fourth();
	else if (step%8==5)
		fith();
	else if (step%8==6)
		sixth();
	else if (step%8==7)
		seventh();
	else
		eigth();
}

/*
// Will try to impliment hand holding for waltz
void hand_holding(int do)
{
    if (do==1)
    {
        for (b=0; b<N_BODIES; b+=2)
        {
            lead_left[b] = dJointCreateBall(dyn_world.id(), 0);
            dJointAttach(lead_left[b], lefthand[b], righthand[b+1]);
            lefthand_pos[b] = dGeomGetPosition(lefthand[b]);

            lead_right[b] = dJointCreateBall(dyn_world.id(), 0);
            dJointAttach(lead_right[b], righthand[b], rightlead_target[b+1]);
            righthand_pos[b] = dGeomGetPosition(righthand[b]);

            follow_left[b+1] = dJointCreateBall(dyn_world.id(), 0);
            dJointAttach(follow_left[b+1], lefthand[b+1], leftfollow_target[b]);
            lefthand_pos[b+1] = dGeomGetPosition(lefthand[b+1]);
        }
    }
    else
    {
    }
}
*/

void display()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(gmtlNavigationMatrix.mData);
    glRotatef(-90.0, 1.0, 0.0, 0.0);

    if(doInteract)
	{
		std::cout << "\nTest interact(int, int) " << cursorX << ' ' << cursorY <<'\n' ;
		interact();
        InteractiveRender();
        endinteract();
		mode = PICK;
		doInteract = false;
	}
	else
	{
		if (dancing == true)
		{
			dance_counter++;
            if (dance_counter%10==0)
            {
                balance();
                stand();
            }
			if (dance_counter%beat==0)
			{
				step++;
				waltz(step);
//  			dance(step);
			}
		}
        cb_sim_step();
        draw();
		glutSwapBuffers();
	}

    GLfloat temp[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, temp);
    trueWorldMatrix.set(temp);

    glPopMatrix();
}


void idle()
{
	dWorldStep (dyn_world,TIME_STEP);

    static clock_t lastTime(clock());
    static clock_t currTime(clock());

    float timeDelta = static_cast< float >((currTime  - lastTime) / CLOCKS_PER_SEC);

    // Time step for sound libray. 
    snx::sonix::instance()->step(timeDelta);

    lastTime = currTime; 
    currTime = clock();
    
	glutPostRedisplay();
}


void reshape(int w, int h)
{
	viewport[2] = w;
	viewport[3] = h;
	
    trackBallDiameter    = (h > w) ? h : w;

	glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)w/h, 0.1, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    gluLookAt(STAGE_SIZE/2, STAGE_SIZE/2, STAGE_SIZE, STAGE_SIZE/2, STAGE_SIZE/2, 0.0, 0.0, 1.0, 0.0);
    glMultMatrixf(gmtlNavigationMatrix.mData);
}


void myGlutTimer(int puase)
{
}

// Intigrates mouse use into program
void mouseplay(int button, int state, int X, int Y)
{
    switch(mode)
    {
        case PICK:
            if (state == 0)
            {
                switch (button)
                {
                    case GLUT_LEFT_BUTTON:
                        cursorX = X;
                        cursorY = Y;
                        doInteract = true;
                        break;
                    case GLUT_MIDDLE_BUTTON:
                        if (clicked!=-1)
                            dJointGroupEmpty (ragdoll_joints[clicked]);
                        break;
                    case GLUT_RIGHT_BUTTON:
                        if (dancing == true)
                            dancing = false;
                        else 
                            dancing = true;
                        break;
                }
            }
            else if (state == 1)
            {
                switch (button)
                {
                    case GLUT_LEFT_BUTTON:
                        cursorX2 = X;
                        cursorY2 = Y;
                        if (name != -N_BODIES)
                            movedoll();
                        break;

                    case GLUT_MIDDLE_BUTTON:
                        break;

                    case GLUT_RIGHT_BUTTON:
                        break;
                }
            }
            break; // ...case PICK

        case NAVIGATE: 
            if((X < viewport[0] || X >  viewport[2]) || 
                (Y < viewport[1] || Y >  viewport[3]))
            {
                return;  
            }

            double x1 = (2.0f * X - trackBallDiameter) / trackBallDiameter;
            double y1 = (trackBallDiameter - 2.0f * Y) / trackBallDiameter;
            double z1 = sqrt(1.0f - (x1 * x1  - y1 * y1));

            if(z1 >= 1.0f)
            {
                z1 = 1.0f;
            }

            lastPosition.set(x1, y1, z1);
            gmtl::normalize(lastPosition);

            if(state == GLUT_DOWN)
            {
                switch(button)
                {
                    case GLUT_LEFT_BUTTON:
                        useMouseLeftButton = true;
                        break;
                    case GLUT_RIGHT_BUTTON:
                        useMouseRightButton = true;
                        break;
                    case GLUT_MIDDLE_BUTTON:
                        useMouseMiddleButton = true;
                        break;
                }
            }
            else if(state == GLUT_UP)
            {
                switch(button)
                {
                    case GLUT_LEFT_BUTTON:
                        useMouseLeftButton = false;
                        break;
                    case GLUT_RIGHT_BUTTON:
                        useMouseRightButton = false;
                        break;
                    case GLUT_MIDDLE_BUTTON: 
                        useMouseMiddleButton = false;
                        break;
                }
            }
            break; // ... case NAVIGATE
    }
}


// Mouse navigation mode
void mouseMotion(int X, int Y)
{
  float dx, dy, dz, gAngle;
  float axis[3];

  if((X < viewport[0] || X >  viewport[2]) ||
      (Y < viewport[1] || Y >  viewport[3] ) )
  {
      return;
  }

  double x1 = (2.0f * X - trackBallDiameter) / trackBallDiameter;
  double y1 = (trackBallDiameter - 2.0f * Y) / trackBallDiameter;
  double z1 = sqrt(1.0f - (x1 * x1  - y1 * y1));

  if(z1 >= 1.0f)
  {
    z1 = 1.0f;
  }

  currentPosition.set(x1, y1, z1);
  gmtl::normalize(currentPosition);

  dx = currentPosition[0] - lastPosition[0];
  dy = currentPosition[1] - lastPosition[1];
  dz = currentPosition[2] - lastPosition[2];

  if(dx || dy || dz)
  {
    axis[0] = lastPosition[1] * currentPosition[2] - lastPosition[2] * currentPosition[1];
    axis[1] = lastPosition[2] * currentPosition[0] - lastPosition[0] * currentPosition[2];
    axis[2] = lastPosition[0] * currentPosition[1] - lastPosition[1] * currentPosition[0];

    gAngle = gmtl::length(gmtl::Vec3f(axis[0], axis[1], axis[2])) * ((180 * 7.0f) / 22.0f);

    if(useMouseLeftButton)
    {
      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
      glLoadIdentity();
      glRotatef(gAngle, axis[0], axis[1], axis[2]);
      GLfloat gNavigationMatrix[16];
      glGetFloatv(GL_MODELVIEW_MATRIX, gNavigationMatrix);
      glPopMatrix();

      gmtl::Matrix44f temp, temp2;
      temp.set( gNavigationMatrix );

      if( dx >= 0 ? dx > dy : dx < dy )
      {
        gmtl::postMult(gmtlNavigationMatrix, temp);
      }
      else
      {
        gmtl::preMult(gmtlNavigationMatrix, temp);
      }

      lastPosition = currentPosition;
    }

    if(useMouseRightButton)
    { 
      glTranslatef(dx * 5.0, dy * 5.0, 0.0);
      lastPosition = currentPosition;
    }

    if(useMouseMiddleButton)
    { 
      glTranslatef(0.0, 0.0, dz * 50.0);
      lastPosition = currentPosition;
    }
  }

  glutPostRedisplay();
}

// Intigrates keyboard use into program
void keyboard (unsigned char key, int x, int y)
{
	switch (key)
	{
	    case 27:
		    exit(0);
		    break;

	    case 32:
		    if(mode == NAVIGATE)
            {
                useMouseLeftButton = false;
                useMouseRightButton = false;
                useMouseMiddleButton = false;
			    mode = PICK;
		    }
            else
			    mode = NAVIGATE;
		    break;
        case 45:
            TIME_STEP/=2;
            break;
        case 61:
            TIME_STEP*=2;
            break;
	}
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);	
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,600);
	glutCreateWindow("Ragdoll-Physics");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

    glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseplay);
    glutMotionFunc(mouseMotion);
	
	glutMainLoop();
	glutTimerFunc(1, myGlutTimer, 1);

	dCloseODE();
	return 0;
}
