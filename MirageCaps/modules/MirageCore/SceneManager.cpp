
#include "MirageCore/SceneManager"
#include "MirageCore/MatDef"
#include "MirageCore/GLTextFactory"
#include "MirageCore/Text"
#include "MirageCore/GlutText"

#include<math"

using namespace MirageCore;

bool LoadTGA(Texture *, char *);	

SceneManager::SceneManager() :
	mNoOfEnemies( 0 )
{}

void SceneManager::init()
{
	mLabyrinthID = createLabyrinth();
	mCarID = createCar( 12.0 );
	mBoxID = createBox( 30.0 );
	mStarID = createStarA( 20.0 ); 
	mAnimeBoxID1 = createFillBox( 50, MirageCore::Fire );
	mAnimeBoxID2 = createFillBox( 50, MirageCore::Cross );

	for( unsigned int i=0; i < mNoOfEnemies; ++i )
	{
		mEnemyCars.push_back( createCar( 12.0 ) );
		setInitialPos( mEnemyCars[i], Vec3f(  270, 270, 0.0 ) );
		setCurrentPos( mEnemyCars[i], getInitialPos(  mEnemyCars[i] ) );
		setInitialRot( mEnemyCars[i], Vec4f( -180.0, 0.0, 0.0, 1.0 ) );	
		setCurrentRot( mEnemyCars[i], getInitialRot(  mEnemyCars[i] ) );	
	}

	setInitialPos( mLabyrinthID, Vec3f( 0.0, 0.0, 0.0 ) );
	setInitialPos( mCarID, Vec3f( -300, 270, 0.0 ) );
	setInitialPos( mBoxID, Vec3f( 0.0, 0.0, 0.0 ) );
	setInitialPos( mStarID, Vec3f( -210, -210, 0.0 ) );
	setInitialPos( mAnimeBoxID1, Vec3f( 0, 0, 0.0 ) );
	setInitialPos( mAnimeBoxID2, Vec3f( 200, 250, 0.0 ) );

	setCurrentPos( mLabyrinthID,  getInitialPos( mLabyrinthID ) );
	setCurrentPos( mCarID, getInitialPos( mCarID ) );
	setCurrentPos( mBoxID, getInitialPos( mBoxID ) );
	setCurrentPos( mStarID, getInitialPos( mStarID ) );
	setCurrentPos( mAnimeBoxID1, getInitialPos( mAnimeBoxID1 ) );
	setCurrentPos( mAnimeBoxID2, getInitialPos( mAnimeBoxID2 ) );

	setInitialRot( mLabyrinthID, Vec4f( 0.0, 0.0, 0.0, 0.0 ) );	
	setInitialRot( mCarID, Vec4f( 0.0, 0.0, 0.0, 0.0 ) );
	setInitialRot( mBoxID, Vec4f( 0.0, 0.0, 0.0, 0.0 ) );
	setInitialRot( mStarID, Vec4f( 0.0, 0.0, 0.0, 0.0 ) );
	setInitialRot( mAnimeBoxID1, Vec4f( 0.0, 0.0, 0.0, 0.0 ) );
	setInitialRot( mAnimeBoxID2, Vec4f( 0.0, 0.0, 0.0, 0.0 ) );

	setCurrentRot( mLabyrinthID, getInitialRot( mLabyrinthID ) );	
	setCurrentRot( mCarID, getInitialRot( mCarID ) );
	setCurrentRot( mBoxID, getInitialRot( mBoxID ) );
	setCurrentRot( mStarID, getInitialRot( mStarID ) );
	setCurrentRot( mAnimeBoxID1, getInitialRot( mAnimeBoxID1 ) );
	setCurrentRot( mAnimeBoxID2, getInitialRot( mAnimeBoxID2 ) );

	// Load the textures now. 
	LoadTGA( &gTexture[0], ".//../data/Textures/YellowCar.tga" );
	LoadTGA( &gTexture[1], ".//../data/Textures/RedCar.tga" );

	for( int i=0; i < 2; ++i )
	{
		glGenTextures(1, &gTexture[i].texID);				
		glBindTexture(GL_TEXTURE_2D, gTexture[i].texID);
		glTexImage2D(GL_TEXTURE_2D, 0, gTexture[i].bpp / 8, gTexture[i].width, gTexture[i].height, 0, gTexture[i].type, GL_UNSIGNED_BYTE, gTexture[i].imageData);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		if (gTexture[i].imageData)						// If Texture Image Exists ( CHANGE )
		{
			free(gTexture[i].imageData);					// Free The Texture Image Memory ( CHANGE )
		}
	}

	// Set texts. 
	mTexts.push_back( GLTextFactory::instance()->create( "GlutText" ) );
	mTexts.push_back( GLTextFactory::instance()->create( "GlutText" ) );
	mTexts[0]->setText( "Start" ); 
	mTexts[0]->setPos( Vec3f( -320.0, 270.0, 0.0 ) );
	mTexts[0]->setScale( Vec3f( 0.2, 0.2, 0.3 ) );
	mTexts[1]->setText( "Finish" ); 
	mTexts[1]->setPos( Vec3f( 275.0, -270.0, 0.0 ) );
	mTexts[1]->setScale( Vec3f( 0.2, 0.2, 0.2 ) );

	mCtrlTexts.push_back( GLTextFactory::instance()->create( "GlutText" ) );
	mCtrlTexts[0]->setText("");
	mCtrlTexts[0]->setPos( Vec3f( -200.0, 0.0, 0.0 ) );
	mCtrlTexts[0]->setScale( Vec3f( 0.1, 0.1, 0.1 ) );

	mCtrlTexts.push_back( GLTextFactory::instance()->create( "GlutText" ) );
	mCtrlTexts[1]->setText("");
	mCtrlTexts[1]->setPos( Vec3f( -20.0, -50.0, 0.0 ) );
	mCtrlTexts[1]->setScale( Vec3f( 0.1, 0.1, 0.1 ) );
}

GLuint SceneManager::createLabyrinth()
{	
	glLineWidth( 4.0 );
	//glEnable( GL_LINE_STIPPLE );
	//glLineStipple( 8, 0xAAAA );
	
	GLuint labyrinthID = glGenLists(1);	
	glNewList( labyrinthID, GL_COMPILE );			
		glLineWidth( 6.0 );
		glBegin( GL_LINE_STRIP );
			glVertex2f( -300.0,  240.0 );
			glVertex2f( -300.0, -300.0 );
			glVertex2f(  270.0, -300.0 );
		glEnd();
		glBegin( GL_LINE_STRIP );
			glVertex2f( -270.0,  300.0 );
			glVertex2f(  300.0,  300.0 );
			glVertex2f(  300.0, -240.0 );
		glEnd();
		glLineWidth( 2.0 );
		glBegin( GL_LINE_STRIP );
			glVertex2f( -240,    120.0 );
			glVertex2f( -240.0,  240.0 );
			glVertex2f( -120.0,  240.0 );
			glVertex2f( -120.0,  120.0 );
		glEnd();
		glBegin( GL_LINE_STRIP );
			glVertex2f( -180,    120.0 );
			glVertex2f( -180.0,  180.0 );
		glEnd();
		glBegin( GL_LINE_STRIP );
			glVertex2f( -240.0,   60.0 );
			glVertex2f(  -60.0,   60.0 );
			glVertex2f(  -60.0,    0.0 );
			glVertex2f( -240.0,    0.0 );
			glVertex2f( -240.0,  -60.0 );
		glEnd();
		glBegin( GL_LINE_STRIP );
			glVertex2f( -300.0,  -120.0 );
			glVertex2f( -180.0,  -120.0 );
			glVertex2f( -180.0,   -60.0 );
			glVertex2f( -120.0,   -60.0 );
			glVertex2f( -120.0,   -60.0 );
			glVertex2f( -120.0,  -240.0 );
		glEnd();
		glBegin( GL_LINE_STRIP );
			glVertex2f( -240.0,  -180.0 );
			glVertex2f( -180.0,  -180.0 );
			glVertex2f( -180.0,  -240.0 );
			glVertex2f( -240.0,  -240.0 );
			glVertex2f( -240.0,  -180.0 );
		glEnd();
		glBegin( GL_LINE_STRIP );
			glVertex2f(  -60.0,  240.0 );
			glVertex2f(  -60.0,  180.0 );
			glVertex2f(    0.0,  180.0 );
		glEnd();
		glBegin( GL_LINE_STRIP );
			glVertex2f(    0.0,  240.0 );
			glVertex2f(  240.0,  240.0 );
		glEnd();
		glBegin( GL_LINE_STRIP );
			glVertex2f(  -60.0,  120.0 );
			glVertex2f(   60.0,  120.0 );
			glVertex2f(   60.0,  180.0 );
			glVertex2f(  120.0,  180.0 );
			glVertex2f(  120.0,   60.0 );
			glVertex2f(   0.0,    60.0 );
			glVertex2f(   0.0,  -180.0 );
		glEnd();
		glBegin( GL_LINE_STRIP );
			glVertex2f(  180.0,  180.0 );
			glVertex2f(  180.0,   60.0 );
			glVertex2f(  300.0,   60.0 );
		glEnd();
		glBegin( GL_LINE_STRIP );
			glVertex2f(   60.0,    0.0 );
			glVertex2f(  180.0,    0.0 );
			glVertex2f(  180.0,   60.0 );
		glEnd();
		glBegin( GL_LINE_STRIP );
			glVertex2f(  240.0,  180.0 );
			glVertex2f(  240.0,  120.0 );
		glEnd();
		glBegin( GL_LINE_STRIP );
			glVertex2f(  120.0,    0.0 );
			glVertex2f(  120.0,  -60.0 );
		glEnd();
		glBegin( GL_LINE_STRIP );
			glVertex2f(  -60.0,  -120.0 );
			glVertex2f(  -60.0,   -60.0 );
			glVertex2f(   60.0,   -60.0 );
		glEnd();
		glBegin( GL_LINE_STRIP );
			glVertex2f(  240.0,     0.0 );
			glVertex2f(  240.0,   -60.0 );
			glVertex2f(  180.0,   -60.0 );
			glVertex2f(  180.0,  -120.0 );
			glVertex2f(   60.0,  -120.0 );
			glVertex2f(   60.0,  -240.0 );
			glVertex2f(  -60.0,  -240.0 );
			glVertex2f(  -60.0,  -180.0 );
		glEnd();
		glBegin( GL_LINE_STRIP );
			glVertex2f(  240.0,  -60.0 );
			glVertex2f(  240.0, -120.0 );
			glVertex2f(  300.0, -120.0 );
		glEnd();
		glBegin( GL_LINE_STRIP );
			glVertex2f(  -60.0,  -120.0 );
			glVertex2f(  -60.0,   -60.0 );
			glVertex2f(   60.0,   -60.0 );
		glEnd();
		glBegin( GL_LINE_STRIP );
			glVertex2f(  180.0,  -120.0 );
			glVertex2f(  180.0,  -180.0 );
		glEnd();
		glBegin( GL_LINE_STRIP );
			glVertex2f(  120.0,  -180.0 );
			glVertex2f(  120.0,  -300.0 );
		glEnd();
		glBegin( GL_LINE_STRIP );
			glVertex2f(  240.0,  -180.0 );
			glVertex2f(  240.0,  -240.0 );
			glVertex2f(  180.0,  -240.0 );
			glVertex2f(  180.0,  -300.0 );
		glEnd();
	glEndList();
	return labyrinthID;
}

GLuint SceneManager::createCar( double size )
{
	GLuint carID = glGenLists( 100 );
	glNewList( carID, GL_COMPILE );
		glScalef( size, size, 0.0 );
		glBegin( GL_TRIANGLE_STRIP );			
			glTexCoord2d( 0.75, 0.0 ); glVertex2f( 1.0, -1.0 );
			glTexCoord2d( 1.0,  0.0 ); glVertex2f( 2.0, -1.0 );
			glTexCoord2d( 1.0,  1.0 ); glVertex2f( 2.0,  1.0 );	
			glTexCoord2d( 0.75, 0.0 ); glVertex2f( 1.0, -1.0 );
			glTexCoord2d( 1.0,  1.0 ); glVertex2f( 2.0,  1.0 );
			glTexCoord2d( 0.75, 1.0 ); glVertex2f( 1.0,  1.0 );
			glTexCoord2d( 0.5,  0.0 ); glVertex2f( 0.0, -1.0 );
			glTexCoord2d( 0.75, 0.0 ); glVertex2f( 1.0, -1.0 );
			glTexCoord2d( 0.75, 0.5 ); glVertex2f( 1.0,  0.0 );
			glTexCoord2d(  0.5, 0.0 ); glVertex2f( 0.0, -1.0 );
			glTexCoord2d( 0.75, 0.5 ); glVertex2f( 1.0,  0.0 );
			glTexCoord2d( 0.5,  1.0 ); glVertex2f( 0.0,  1.0 );
			glTexCoord2d( 0.5,  0.5 ); glVertex2f( 0.0,  0.0 );
			glTexCoord2d( 0.75, 0.5 ); glVertex2f( 1.0,  0.0 );
			glTexCoord2d( 0.5,  1.0 ); glVertex2f( 1.0,  1.0 );
			glTexCoord2d( 0.5,  0.5 ); glVertex2f( 0.0,  0.0 );
			glTexCoord2d( 0.75, 1.0 ); glVertex2f( 1.0,  1.0 );
			glTexCoord2d( 0.5,  1.0 ); glVertex2f( 0.0,  1.0 );
			glTexCoord2d( 0.25, 0.0 ); glVertex2f(-1.0, -1.0 );
			glTexCoord2d( 0.5,  0.0 ); glVertex2f( 0.0, -1.0 );
			glTexCoord2d( 0.5,  1.0 ); glVertex2f( 0.0,  1.0 );
			glTexCoord2d( 0.25, 0.0 ); glVertex2f(-1.0, -1.0 );
			glTexCoord2d( 0.5,  1.0 ); glVertex2f( 0.0,  1.0 );
			glTexCoord2d( 0.25, 1.0 ); glVertex2f(-1.0,  1.0 );
			glTexCoord2d( 0.0,  0.0 ); glVertex2f(-2.0, -1.0 );
			glTexCoord2d( 0.25, 0.0 ); glVertex2f(-1.0, -1.0 );
			glTexCoord2d( 0.25, 1.0 ); glVertex2f(-1.0,  1.0 );
			glTexCoord2d( 0.0,  0.0 ); glVertex2f(-2.0, -1.0 );
			glTexCoord2d( 0.25, 1.0 ); glVertex2f(-1.0,  1.0 );
			glTexCoord2d( 0.0,  1.0 ); glVertex2f(-2.0,  1.0 );
		glEnd();			
	glEndList();
	return carID;
}

GLuint SceneManager::createBox( double size )
{
	GLuint boxID = glGenLists( 100 );
	glNewList( boxID, GL_COMPILE );
		glScalef( size, size, 0.0 );
		glBegin( GL_LINE_LOOP );
			glVertex2f( -1.0, -1.0 );
			glVertex2f(  1.0, -1.0 );
			glVertex2f(  1.0,  1.0 );
			glVertex2f( -1.0,  1.0 );
		glEnd();
	glEndList();

	return boxID;
}

GLuint SceneManager::createFillBox( double size, const GLubyte* mask )
{
	GLuint boxID = glGenLists( 100 );
	glNewList( boxID, GL_COMPILE );
		glScalef( size, size, 0.0 );
		glEnable( GL_POLYGON_STIPPLE );
		glPolygonStipple( mask );
		glBegin( GL_POLYGON );
			glVertex2f( -1.0, -1.0 );
			glVertex2f(  1.0, -1.0 );
			glVertex2f(  1.0,  1.0 );
			glVertex2f( -1.0,  1.0 );
		glEnd();
		glDisable( GL_POLYGON_STIPPLE );
	glEndList();	
	return boxID;
} 

GLuint SceneManager::createStarA( double size )
{
	GLuint starID = glGenLists( 100 );
	glNewList( starID, GL_COMPILE );
		glScalef( size, size, 0.0 );
		createStar();
	glEndList();
	return starID;	
}

void SceneManager::createStar()
{
	glBegin( GL_TRIANGLE_FAN );
		glNormal3f( 0.0, 0.0, 1.0 );
		glVertex2f(  0.0,  0.0 );
		glNormal3f( 0.0, 1.0, 0.0 );
		glVertex2f(  1.0,  2.0 );
		glNormal3f( 1.0, 0.0, 0.0 );
		glVertex2f( -1.0,  2.0 );
		glNormal3f( 0.0, 0.0, 1.0 );
		glVertex2f(  0.0,  0.0 );
		glNormal3f( 0.0, 1.0, 0.0 );
		glVertex2f( -2.0,  1.0 );
		glNormal3f( 1.0, 0.0, 0.0 );
		glVertex2f( -2.0, -1.0 );
		glNormal3f( 0.0, 0.0, 1.0 );
		glVertex2f(  0.0,  0.0 );
		glNormal3f( 0.0, 1.0, 0.0 );
		glVertex2f( -1.0, -2.0 );
		glNormal3f( 1.0, 0.0, 0.0 );
		glVertex2f(  1.0, -2.0 );
		glNormal3f( 0.0, 0.0, 0.0 );
		glVertex2f(  0.0,  0.0 );
		glNormal3f( 0.0, 1.0, 0.0 );
		glVertex2f(  2.0, -1.0 );
		glNormal3f( 1.0, 0.0, 0.0 );
		glVertex2f(  2.0,  1.0 );
		glNormal3f( 0.0, 0.0, 1.0 );
	glEnd();	
}

void SceneManager::setInitialPos( unsigned int index, Vec3f pos )
{
	mMapIndexToInitPos[index] = pos;
}

Vec3f SceneManager::getInitialPos( const unsigned int index )
{
	return mMapIndexToInitPos[index];
}

void SceneManager::setCurrentPos( unsigned int index, Vec3f pos )
{
	mMapIndexToCurrPos[index] = pos;
}

Vec3f SceneManager::getCurrentPos( const unsigned int index )
{
	return mMapIndexToCurrPos[index];
}

void SceneManager::setInitialRot( unsigned int index, Vec4f rot )
{
	mMapIndexToInitRot[index] = rot;
}

Vec4f SceneManager::getInitialRot( const unsigned int index )
{
	return mMapIndexToInitRot[index];
}

void SceneManager::setCurrentRot( unsigned int index, Vec4f rot )
{
	mMapIndexToCurrRot[index] = rot;
}

Vec4f SceneManager::getCurrentRot( const unsigned int index )
{
	return mMapIndexToCurrRot[index];
}

void SceneManager::setNoOfEnemies( long int count )
{
	mNoOfEnemies = count;
}

long int SceneManager::getNoOfEnemies()
{
	return mNoOfEnemies;
}

Text* SceneManager::getText( unsigned int i )
{
	if( i < mTexts.size() )
	{
		return mTexts[i];
	}
	else
	{
		return 0;
	}
}

Text* SceneManager::getCtrlText( unsigned int i )
{
	if( i < mCtrlTexts.size() )
	{
		return mCtrlTexts[i];
	}
	else
	{
		return 0;
	}
}

void SceneManager::draw()
{
	// Draw labyrith. 
	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, MirageCore::gMatDiffuse2 );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, MirageCore::gMatSpecular2 );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, MirageCore::gMatShininess2 );
	glCallList( mLabyrinthID );	
	
	// Draw car. 	
	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, MirageCore::gMatDiffuse6 );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, MirageCore::gMatSpecular6 );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, MirageCore::gMatShininess6 );
	Vec3f vecTrans = getCurrentPos( mCarID );
	Vec4f vecRot   = getCurrentRot( mCarID );
	glPushMatrix();
		glLoadIdentity();
		glTranslatef( vecTrans[0], vecTrans[1], vecTrans[2] );
		glRotatef( vecRot[0], vecRot[1], vecRot[2], vecRot[3] );		
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, gTexture[0].texID );
		glCallList( mCarID );			
	glPopMatrix();		

	// Draw enemy cars. 
	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, MirageCore::gMatDiffuse6 );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, MirageCore::gMatSpecular6 );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, MirageCore::gMatShininess6 );
	for( int i=0; i < mNoOfEnemies; ++i )
	{
		Vec3f vecTrans = getCurrentPos( mEnemyCars[i] );
		Vec4f vecRot   = getCurrentRot( mEnemyCars[i] );
		glPushMatrix();
			glLoadIdentity();
			glTranslatef( vecTrans[0], vecTrans[1], vecTrans[2] );
			glRotatef( vecRot[0], vecRot[1], vecRot[2], vecRot[3] );		
			glEnable( GL_TEXTURE_2D );
			glBindTexture( GL_TEXTURE_2D, gTexture[1].texID );
			glCallList( mEnemyCars[i] );			
		glPopMatrix();		
	}

	// Draw start.
	glDisable( GL_TEXTURE_2D );
	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, MirageCore::gMatDiffuse5 );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, MirageCore::gMatSpecular5 );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, MirageCore::gMatShininess5 );
	glPushMatrix();
		glTranslatef( -300.0, 270.0, 0.0 );
		glCallList( mBoxID );
	glPopMatrix();

	// Draw end. 
	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, MirageCore::gMatDiffuse3 );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, MirageCore::gMatSpecular3 );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, MirageCore::gMatShininess3 );
	glPushMatrix();
		glTranslatef( 300.0, -270.0, 0.0 );
		glCallList( mBoxID );
	glPopMatrix();	

	// Draw Pattern. 
	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, MirageCore::gMatDiffuse7 );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, MirageCore::gMatSpecular7 );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, MirageCore::gMatShininess7 );
	vecTrans = getCurrentPos( mAnimeBoxID1 );
	glPushMatrix();
		glTranslatef( vecTrans[0], vecTrans[1], vecTrans[2] );
		glCallList( mAnimeBoxID1 );
	glPopMatrix();

	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, MirageCore::gMatDiffuse5 );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, MirageCore::gMatSpecular5 );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, MirageCore::gMatShininess5 );
	vecTrans = getCurrentPos( mAnimeBoxID2 );
	glPushMatrix();
		glTranslatef( vecTrans[0], vecTrans[1], vecTrans[2] );
		glCallList( mAnimeBoxID2 );
	glPopMatrix();

	// Draw Star.
	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, MirageCore::gMatDiffuse3 );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, MirageCore::gMatSpecular3 );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, MirageCore::gMatShininess3 );
	vecTrans = getCurrentPos( mStarID );
	vecRot   = getCurrentRot( mStarID );
	glPushMatrix();
		glLoadIdentity();
		glTranslatef( vecTrans[0], vecTrans[1], vecTrans[2] );
		glRotatef( vecRot[0], vecRot[1], vecRot[2], vecRot[3] );
		glCallList( mStarID );
	glPopMatrix();	

	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, MirageCore::gMatDiffuse6 );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, MirageCore::gMatSpecular6 );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, MirageCore::gMatShininess6 );
	for( size_t i=0; i < mTexts.size(); ++i )
	{
		mTexts[i]->draw();
	}

	// Draw double orbit. 
	glPushMatrix();
		glLoadIdentity();
		glTranslatef( 100.0, 30.0, 0.0 );	
		glScalef( 0.5, 0.5, 0.5 );
		glCallList( mStarID );
	glPopMatrix();	

	static double theta = 0.0;
	static double x = 0.0;	
	static double y = 0.0;

	glPushMatrix();
		glLoadIdentity();
		glTranslatef( x, y, 0.0 );
		glScalef( 0.5, 0.5, 0.5 );
		glCallList( mStarID );
	glPopMatrix();	

	static double theta2 = 0.0;
	static double x2 = 0.0;	
	static double y2= 0.0;

	glPushMatrix();
		glLoadIdentity();
		glTranslatef( x2, y2, 0.0 );
		glScalef( 0.5, 0.5, 0.5 );
		glCallList( mStarID );
	glPopMatrix();	

	theta2 = theta2 + 0.02;
	if( theta2 >= 6.28 )
		theta2 = 0.0;
	x2 = 40.0 * cos( theta2 ) + x;
	y2 = 40.0 * sin( theta2 ) + y;


	theta = theta + 0.01;
	if( theta >= 6.28 )
		theta = 0.0;
	x = 40.0 * cos( theta ) + 100.0;
	y = 40.0 * sin( theta ) + 30.0;


	// Static orbit. 
	// Draw double orbit. 
	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, MirageCore::gMatDiffuse1 );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, MirageCore::gMatSpecular1 );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, MirageCore::gMatShininess1 );
	glPushMatrix();
		glLoadIdentity();
		glTranslatef( 210.0, -90.0, 0.0 );		
		glCallList( mStarID );
	glPopMatrix();	

	static double theta3 = 0.0;
	static double x3 = 0.0;	
	static double y3 = 0.0;

	glPushMatrix();
		glLoadIdentity();
		glTranslatef( x3, y3, 0.0 );		
		glScalef( 0.5, 0.5, 0.5 );
		glCallList( mStarID );
	glPopMatrix();	
	
	theta3 = theta3 + 0.01;
	if( theta3 >= 6.28 )
		theta3 = 0.0;
	x3 = 50.0 * cos( theta3 ) + 210.0;
	y3 = 50.0 * sin( theta3 ) + -90.0;

}

void SceneManager::drawControls()
{
	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, MirageCore::gMatDiffuse6 );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, MirageCore::gMatSpecular6 );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, MirageCore::gMatShininess6 );
	for( size_t i=0; i < mCtrlTexts.size(); ++i )
	{
		mCtrlTexts[i]->draw();
	}
}