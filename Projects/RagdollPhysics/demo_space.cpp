// Test my Plane2D constraint.
// Uses ode-0.35 collision API.

// uses Juniper wood manikins of density 508 kg/m^3

// Testing.....

# include	<stdio.h>
# include	<stdlib.h>
# include	<math.h>
# include	<iostream>
# include	<ode/ode.h>
# include	<drawstuff/drawstuff.h>
# include	"texturepath.h"
# include	"GL/glut.h"

#   define drand48()  ((double) (((double) rand()) / ((double) RAND_MAX)))

# define BUFSIZE  512
GLuint selectBuf[BUFSIZE];

//number of manikins
# define        N_BODIES        20


# define        STAGE_SIZE      8.0  // in m
# define        TIME_STEP       0.0002

//sponginess
# define        K_SPRING        1.0
# define        K_DAMP          1.0

double timeAccum;
double lastTime;
//using namespace ode;

int puase = 0;
bool friction = true;
int viewing = 1;


//names the world in which the collisions take place
static dWorld   dyn_world;


//density of manikins in kg/m^3  (sun baked dried Chinese Juniper Wood)
static dReal    density = 508;


//necessary for collisions
static dSpaceID coll_space_id;
static dJointID plane2d_joint_ids[N_BODIES];
static dJointGroup coll_contacts;

//names objects
static dBodyID  torso1[N_BODIES];
static dBodyID  torso2[N_BODIES];
static dBodyID  torso3[N_BODIES];
static dBodyID  head[N_BODIES];
static dBodyID  leftarm1[N_BODIES];
static dBodyID  leftarm2[N_BODIES];
static dBodyID  rightarm1[N_BODIES];
static dBodyID  rightarm2[N_BODIES];
static dBodyID  leftleg1[N_BODIES];
static dBodyID  leftleg2[N_BODIES];
static dBodyID  rightleg1[N_BODIES];
static dBodyID  rightleg2[N_BODIES];


//names shapes to be applied to objects later
static dGeomID  torso1_geom[N_BODIES];
static dGeomID  torso2_geom[N_BODIES];
static dGeomID  torso3_geom[N_BODIES];
static dGeomID  head_geom[N_BODIES];
static dGeomID  leftarm1_geom[N_BODIES];
static dGeomID  leftarm2_geom[N_BODIES];
static dGeomID  rightarm1_geom[N_BODIES];
static dGeomID  rightarm2_geom[N_BODIES];
static dGeomID  leftleg1_geom[N_BODIES];
static dGeomID  leftleg2_geom[N_BODIES];
static dGeomID  rightleg1_geom[N_BODIES];
static dGeomID  rightleg2_geom[N_BODIES];


//makes all the joints of one manikin into a single unit makes an array of them
static dJointGroupID ragdoll_joints[N_BODIES];


//names joint constraints
static dJointID rib1[N_BODIES];
static dJointID rib2[N_BODIES];
static dJointID neck[N_BODIES];
static dJointID leftsholder[N_BODIES];
static dJointID rightsholder[N_BODIES];
static dJointID leftelbow[N_BODIES];
static dJointID rightelbow[N_BODIES];
static dJointID lefthip[N_BODIES];
static dJointID righthip[N_BODIES];
static dJointID leftknee[N_BODIES];
static dJointID rightknee[N_BODIES];


// rendering parameters.
int viewport[] = { 0, 0, 800, 600 };

static bool doInteract = false;
static int  cursorX;
static int  cursorY;


void draw()
    {
	// ode  drawstuff
	
	//glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );

	glBegin( GL_QUADS );
		glVertex3f( -100.0, -100.0, 0.0 );
		glVertex3f(  100.0, -100.0, 0.0 );
		glVertex3f(  100.0, 100.0, 0.0 );
		glVertex3f( -100.0, 100.0, 0.0 );
	glEnd();

	dsSetColor (0.9, 0.6, 0.4);
	for (int b = 0; b < N_BODIES; b ++)
	{

#ifdef dDOUBLE



	dsDrawCapsuleD (dGeomGetPosition(torso1_geom[b]),dGeomGetRotation(torso1_geom[b]),.1,.1);
	dsDrawSphereD (dGeomGetPosition(torso2_geom[b]),dGeomGetRotation(torso2_geom[b]),.1);
	dsDrawSphereD (dGeomGetPosition(torso3_geom[b]),dGeomGetRotation(torso3_geom[b]),.1);

	dsDrawSphereD (dGeomGetPosition(head_geom[b]),dGeomGetRotation(head_geom[b]),.075);

	dsDrawCapsuleD (dGeomGetPosition(leftarm1_geom[b]),dGeomGetRotation(leftarm1_geom[b]),.3,.05);
	dsDrawCapsuleD (dGeomGetPosition(leftarm2_geom[b]),dGeomGetRotation(leftarm2_geom[b]),.3,.05);

	dsDrawCapsuleD (dGeomGetPosition(rightarm1_geom[b]),dGeomGetRotation(rightarm1_geom[b]),.3,.05);
	dsDrawCapsuleD (dGeomGetPosition(rightarm2_geom[b]),dGeomGetRotation(rightarm2_geom[b]),.3,.05);

	dsDrawCapsuleD (dGeomGetPosition(leftleg1_geom[b]),dGeomGetRotation(leftleg1_geom[b]),.4,.05);
	dsDrawCapsuleD (dGeomGetPosition(leftleg2_geom[b]),dGeomGetRotation(leftleg2_geom[b]),.4,.05);

	dsDrawCapsuleD (dGeomGetPosition(rightleg1_geom[b]),dGeomGetRotation(rightleg1_geom[b]),.4,.05);
	dsDrawCapsuleD (dGeomGetPosition(rightleg2_geom[b]),dGeomGetRotation(rightleg2_geom[b]),.4,.05);

#else


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

# endif
	}
    }



//creates tempotary jiont constraints for coliding objects
static void     cb_near_collision (void *data, dGeomID o1, dGeomID o2)
/********************************************************************/
{
	dBodyID		b1 = dGeomGetBody (o1);
	dBodyID		b2 = dGeomGetBody (o2);
	dContact	contact;


// exit without doing anything if the two bodies are static
	if (b1 == 0 && b2 == 0)
		return;

// exit without doing anything if the two bodies are connected by a joint
	if (b1 && b2 && dAreConnected (b1, b2))
	{
		/* MTRAP; */
		return;
	}

	contact.surface.mode = 0;
	contact.surface.mu = 100; // static friction I belive);


	if (dCollide (o1, o2, 1, &contact.geom, sizeof (dContactGeom)))
	{
		dJointID c = dJointCreateContact (dyn_world.id(), coll_contacts.id (), &contact);
		dJointAttach (c, b1, b2);
	}
}



void Friction()
{

//this is a switch for turning on or off the friction (1 = on, 0 = off)
if (friction == true)  /* [ */
    {
	// basic aproximation for kenetic air and ground friction 
	for (int b = 0; b < N_BODIES; b ++)
	{
	//linear slowing due to air friction
	dReal       s = 1-0.001*1000/density;
	//angular slowing due to air friction
        dReal       t = 1-0.002*1000/density;
	//linear slowing due to ground frinction
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
			*hight_leftarm1 = dBodyGetPosition (leftarm1[b]);
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

	const dReal	*vel_leftarm2 = dBodyGetLinearVel (leftarm2[b]),
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

	const dReal	*vel_rightarm1 = dBodyGetLinearVel (rightarm1[b]),
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


void interact(int cursorX, int cursorY)
{
	//sets up interactivity

	//GLint viewport[4];

	glSelectBuffer(BUFSIZE,selectBuf);
	glRenderMode(GL_SELECT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	//glGetIntegerv(GL_VIEWPORT, viewport);
	gluPickMatrix(cursorX, viewport[3]-cursorY, 5, 5, viewport);
	gluPerspective(60, viewport[2]/viewport[3], 1.0, 1000);
	glMatrixMode(GL_MODELVIEW);
	glInitNames();
}

void processHits (GLint hits, GLuint buffer[])
{

std::cout<<"# of hits "<<hits<<'\n';

}


void endinteract()
{

	int hits;

	// restoring the original projection matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glFlush();

	// returning to normal rendering mode
	hits = glRenderMode(GL_RENDER);
	std::cout << "hits are: " << hits << std::endl;

	// if there are hits process them
	if (hits != 0)
	{
		std::cout << "hits are: " << hits << std::endl;
		processHits(hits,selectBuf);
	}
}




	//incompatibility issues between gl and ds
void InteractiveRender ()
{
	//glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );

	glBegin( GL_QUADS );
		glVertex3f( -100.0, -100.0, 0.0 );
		glVertex3f(  100.0, -100.0, 0.0 );
		glVertex3f(  100.0, 100.0, 0.0 );
		glVertex3f( -100.0, 100.0, 0.0 );
	glEnd();

	dsSetColor (0.9, 0.6, 0.4);
	for (int b = 0; b < N_BODIES; b ++)
	{

#ifdef dDOUBLE




	glInitNames();
	glPushName(b);

	dsDrawCapsuleD (dGeomGetPosition(torso1_geom[b]),dGeomGetRotation(torso1_geom[b]),.1,.1);
	glLoadName(b+N_BODIES);
	dsDrawSphereD (dGeomGetPosition(torso2_geom[b]),dGeomGetRotation(torso2_geom[b]),.1);
	glLoadName(b+N_BODIES*2);
	dsDrawSphereD (dGeomGetPosition(torso3_geom[b]),dGeomGetRotation(torso3_geom[b]),.1);

	glLoadName(b+N_BODIES*3);
	dsDrawSphereD (dGeomGetPosition(head_geom[b]),dGeomGetRotation(head_geom[b]),.075);

	glLoadName(b+N_BODIES*4);
	dsDrawCapsuleD (dGeomGetPosition(leftarm1_geom[b]),dGeomGetRotation(leftarm1_geom[b]),.3,.05);
	glLoadName(b+N_BODIES*5);
	dsDrawCapsuleD (dGeomGetPosition(leftarm2_geom[b]),dGeomGetRotation(leftarm2_geom[b]),.3,.05);

	glLoadName(b+N_BODIES*6);
	dsDrawCapsuleD (dGeomGetPosition(rightarm1_geom[b]),dGeomGetRotation(rightarm1_geom[b]),.3,.05);
	glLoadName(b+N_BODIES*7);
	dsDrawCapsuleD (dGeomGetPosition(rightarm2_geom[b]),dGeomGetRotation(rightarm2_geom[b]),.3,.05);

	glLoadName(b+N_BODIES*8);
	dsDrawCapsuleD (dGeomGetPosition(leftleg1_geom[b]),dGeomGetRotation(leftleg1_geom[b]),.4,.05);
	glLoadName(b+N_BODIES*9);
	dsDrawCapsuleD (dGeomGetPosition(leftleg2_geom[b]),dGeomGetRotation(leftleg2_geom[b]),.4,.05);

	glLoadName(b+N_BODIES*10);
	dsDrawCapsuleD (dGeomGetPosition(rightleg1_geom[b]),dGeomGetRotation(rightleg1_geom[b]),.4,.05);
	glLoadName(b+N_BODIES*11);
	dsDrawCapsuleD (dGeomGetPosition(rightleg2_geom[b]),dGeomGetRotation(rightleg2_geom[b]),.4,.05);
	glPopName();
	}

#else



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

# endif
	




}

// updates program at each time step
static void     cb_sim_step ()
/*************************************/
{

	const int n = 10;
	for (int i = 0; i < n; i ++)
	{
		dSpaceCollide (coll_space_id, 0, &cb_near_collision);
		dyn_world.step (dReal(TIME_STEP/n));
		coll_contacts.empty ();
	}



	Friction();

	switch (viewing)
	{
		case 1:
			InteractiveRender();
			break;
		case 2:
			InteractiveRender();
			break;
	}
}



//sets initial parameters
void init()
{
	int b;

	dInitODE2(0);

	// Let bodies move into each other a bit.
	dReal  cf_mixing;// = 1 / TIME_STEP * K_SPRING + K_DAMP;
	dReal  err_reduct;// = TIME_STEP * K_SPRING * cf_mixing;
	err_reduct = REAL( 0.5 );
	cf_mixing = REAL( 0.001 );
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


	//Four walls
	dCreatePlane (coll_space_id,  1, 0, 0, 0);
	dCreatePlane (coll_space_id, -1, 0, 0, -STAGE_SIZE);
	dCreatePlane (coll_space_id,  0,  1, 0, 0);
	dCreatePlane (coll_space_id,  0, -1, 0, -STAGE_SIZE);

	coll_contacts.create (0);

	for (b = 0; b < N_BODIES; b ++)
	{
		int     l = (int) (1 + sqrt ((double) N_BODIES));
		dReal  x = dReal( (0.5 + (b / l)) / l * STAGE_SIZE );
		dReal  y = dReal( (0.5 + (b % l)) / l * STAGE_SIZE );
		dReal  z = REAL( 1.2 );


		//center of mass hight (torso2)
		dReal z1 = z;

		//head hight
		dReal zhead = z+ 0.375;

		//neck hight
		dReal zneck = z+ 0.3;

		//sholder hight
		dReal zsholder = z+ 0.25;

		//elbow hight
		dReal zelbow = z+ 0.55;

		//hip hight
		dReal zhip = z- 0.2;

		//knee hight
		dReal zknee = z- 0.6;

		//center of body
		dReal x1 = x;

		//left sholder/hip position
		dReal x2 = x+ 0.1;

		//right sholder/hip position
		dReal x3 = x- 0.1;


// creates objects and assigns names
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


// creates shapes and assigns names and bodies
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


		//positions bodies/shapes
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


		//makes things oriented up
		dMatrix3 dir = {1,1,1,1,1,1,1,1,1,1,1,1};
		dGeomSetRotation(torso1_geom[b], dir );
		dGeomSetRotation(torso2_geom[b], dir );
		dGeomSetRotation(torso3_geom[b], dir );
		dGeomSetRotation(head_geom[b], dir );
		dGeomSetRotation(leftarm1_geom[b],dir );
		dGeomSetRotation(leftarm2_geom[b],dir );
		dGeomSetRotation(rightarm1_geom[b],dir );
		dGeomSetRotation(rightarm2_geom[b],dir );
		dGeomSetRotation(leftleg1_geom[b], dir );
		dGeomSetRotation(leftleg2_geom[b], dir );
		dGeomSetRotation(rightleg1_geom[b],dir );
		dGeomSetRotation(rightleg2_geom[b],dir );


		//makes a group for the joints to join
		ragdoll_joints[b] = dJointGroupCreate (0);



		//makes, assigns a name to, attaches, and places joints

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


		//gives mass to manikins
		dMass m;

		// gives torso1 mass
		dMassSetCappedCylinder (&m, density, (0,0,1), REAL(0.05), REAL(0.6));
		dMassTranslate (&m, x, y, z+ 0.2);		

		// gives torso2 mass
		dMassSetSphere (&m, density, REAL(0.1));
		dMassTranslate (&m, x, y, z);

		// gives torso3 mass
		dMassSetSphere (&m, density, REAL(0.1));
		dMassTranslate (&m, x, y, z- 0.2);

		// gives head mass
		dMassSetSphere (&m, density, REAL(0.075));
		dMassTranslate (&m, x, y, z+ 0.4);

		// gives leftarm1 mass
		dMassSetCappedCylinder (&m, density, (0,0,1), REAL(0.05), REAL(0.3));
		dMassTranslate (&m, x, y + 0.1, z + 0.4);

		// gives leftarm2 mass
		dMassSetCappedCylinder (&m, density, (0,0,1), REAL(0.05), REAL(0.3));
		dMassTranslate (&m, x, y + 0.1, z + 0.7);

		// gives rightarm1 mass
		dMassSetCappedCylinder (&m, density, (0,0,1), REAL(0.05), REAL(0.3));
		dMassTranslate (&m, x, y - 0.1, z + 0.4);

		// gives rightarm2 mass
		dMassSetCappedCylinder (&m, density, (0,0,1), REAL(0.05), REAL(0.3));
		dMassTranslate (&m, x, y - 0.1, z + 0.7);

		// gives leftleg1 mass
		dMassSetCappedCylinder (&m, density, (0,0,1), REAL(0.05), REAL(0.4));
		dMassTranslate (&m, x, y + 0.1, z - 0.4);

		// gives leftleg2 mass
		dMassSetCappedCylinder (&m, density, (0,0,1), REAL(0.05), REAL(0.4));
		dMassTranslate (&m, x, y + 0.1, z - 0.8);

		// gives rightleg1 mass
		dMassSetCappedCylinder (&m, density, (0,0,1), REAL(0.05), REAL(0.4));
		dMassTranslate (&m, x, y - 0.1, z - 0.4);

		// gives rightleg2 mass
		dMassSetCappedCylinder (&m, density, (0,0,1), REAL(0.05), REAL(0.4));
		dMassTranslate (&m, x, y - 0.1, z - 0.8);


	}

	// setup stuff
	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);
	glDisable (GL_TEXTURE_2D);
	glDisable (GL_TEXTURE_GEN_S);
	glDisable (GL_TEXTURE_GEN_T);
	glShadeModel (GL_FLAT);
	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LESS);
	glEnable (GL_CULL_FACE);
	glCullFace (GL_BACK);
	glFrontFace (GL_CCW);

	// leave openGL in a known state - flat shaded white, no textures
	glEnable (GL_LIGHTING);
	glDisable (GL_TEXTURE_2D);
	glShadeModel (GL_FLAT);
	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LESS);
	glColor3f (1,1,1);	



}

void display()
{
	glClearColor( 0.0, 0.0, 0.0, 0.0 );
	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );

	if( doInteract )
	{
		std::cout << "Test interact( int, int ) " << cursorX << " " << cursorY << std::endl;			
		interact( cursorX, cursorY );	
		cb_sim_step();
		endinteract();
		viewing = 1;
		doInteract = false;
		//InteractiveRender();
	}
	else
	{
		cb_sim_step();
	}

	glutSwapBuffers();
}


void idle()
{
	//glClearColor( 0.0, 0.0, 0.0, 0.0 );
	//glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );

	dWorldStep (dyn_world,TIME_STEP);

	//cb_sim_step();void dsDrawFrame (int width, int height, dsFunctions *fn, int pause)	

	//drawGround();

	glColor3f( 0.5, 0.5, 0.5 );
	//cb_sim_step();
		
	glutPostRedisplay();
	//glutSwapBuffers();
}


void reshape(int w, int h)
{
	viewport[2] = w;
	viewport[3] = h;
	
	glViewport( viewport[0], viewport[1], viewport[2], viewport[3] );

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 60.0, w/h, 1.0, 10000.0 );

	glMatrixMode(GL_MODELVIEW);
	gluLookAt(STAGE_SIZE/2, STAGE_SIZE/2, STAGE_SIZE, STAGE_SIZE/2, STAGE_SIZE/2, 0.0, 0.0, 1.0, 0.0);
}


void myGlutTimer( int pause )
{
/*
	double now = 1;
	timeAccum += (now - lastTime);
	lastTime = now;
	while (timeAccum >= TIME_STEP)
	{
		//collideStuff();
		cb_sim_step();
		timeAccum -= TIME_STEP;
	}
*/
}




void mouseplay(int button, int state, int X, int Y)
{
	switch (viewing)
	{
	case 1:
		if ( state == 0 )
		{
			switch ( button )
			{
			case GLUT_LEFT_BUTTON:
				break;
			case GLUT_MIDDLE_BUTTON:
				break;
			case GLUT_RIGHT_BUTTON:
				break;
			}
		}
		else if ( state == 1 )
		{
			switch ( button )
			{
			case GLUT_LEFT_BUTTON:
				friction = true;
				break;
			case GLUT_MIDDLE_BUTTON:
			{
				
				viewing = 2;

				doInteract = true;
				std::cout << "doInteract " << doInteract << std::endl;
				cursorX = X;
				cursorY = Y;	
				//interact(X, Y);
//				endinteract();
				break;
			}
			case GLUT_RIGHT_BUTTON:
				friction = false;
				break;
			}
		}
		break;
	case 2:
		if ( state == 0 )
		{
			switch ( button )
			{
			case GLUT_LEFT_BUTTON:
				break;
			case GLUT_MIDDLE_BUTTON:
//				interact(X, Y);
//				endinteract();
				break;
			case GLUT_RIGHT_BUTTON:
				break;
			}
		}
		else if ( state == 1 )
		{
			switch ( button )
			{
			case GLUT_LEFT_BUTTON:
				friction = true;
				break;
			case GLUT_MIDDLE_BUTTON:
				viewing = 1;
				break;
			case GLUT_RIGHT_BUTTON:
				friction = false;
				break;
			}
		}
		break;
	}

	glutPostRedisplay();
}




int main( int argc, char **argv )
{
	glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);	
	glutInitWindowPosition(100,100);
	glutInitWindowSize(680,510);
	glutCreateWindow("Ragdoll-Physics");

	init();

	glutDisplayFunc( display );
	glutReshapeFunc( reshape );
	glutIdleFunc( idle );



	glutMouseFunc(mouseplay);


	//dsDrawFrame( 680, 420, &drawstuff_functions, 1 );

	//dsSimulationLoop (argc, argv, 352,288,&drawstuff_functions);
	
	glutMainLoop();
	glutTimerFunc( 1, myGlutTimer, 1 );

	dCloseODE();

	return 0;
}
