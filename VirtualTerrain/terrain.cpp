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



NodePtr localModel (  UInt8* black_white_image_data_recived,  UInt32 width,   Pnt3f hit_point, bool event, float scale_value ,  Vec3f * P_recived, float angle_of_rotation);

osg::Matrix rotation (  UInt8* black_white_image_data_recived,  UInt32 width, Pnt3f hit_point, float angle_of_rotation, float scale_value);
const float scale = 0.8; 

GroupNodePtr n ;

Matrix geometrymatrix;
 
UInt32  width, height;
 
UInt8* black_white_image_data;
 
std::vector<NodePtr> localRoots;

std::vector<NodePtr> localRoots1;

GeometryPtr geo;

ImageRefPtr colour_image, black_white, housing_image, empty_image ;
 


		 
 ofstream outputFile("c:vinay\\terrain_generation\\output.txt");
 
 ////keyboard fuction to handel all teh keyboard inputs
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
                    
                        NodePtr SourceNode = localModel( black_white_image_data, width, hit_point, 1, 1.0, 0, 0.0);        ////calling the function //////////////
                        localRoots.push_back(SourceNode);
                   
                        
                }
                
              
                beginEditCP(n, Node::ChildrenFieldMask );
                
                        for(int i=0; i<localRoots.size(); ++i)
                                n.node()->addChild( localRoots[i] );
                
                        
	        endEditCP(n, Node::ChildrenFieldMask );
                
                
                     
         }
         
         if(key == '2')
         {      
	       SimpleTexturedMaterialPtr tex = SimpleTexturedMaterial::create();
	        beginEditCP(tex);
		        tex->setImage(housing_image);
	        endEditCP(tex);
	        
	       
	        beginEditCP(geo, Geometry::MaterialFieldMask );

		        geo->setMaterial( tex );
		    
	        endEditCP(geo,  Geometry::MaterialFieldMask );
	        
         }
         
         if(key == '1')
         {          
	     
	        
	      SimpleTexturedMaterialPtr tex = SimpleTexturedMaterial::create();
	        beginEditCP(tex);
		        tex->setImage( colour_image);
	        endEditCP(tex);
	        
	       
	        beginEditCP(geo, Geometry::MaterialFieldMask );

		        geo->setMaterial( tex );
		    
	        endEditCP(geo,  Geometry::MaterialFieldMask );
	        
	       
	        
         }
         
         if(key == '3')
         {               
               
	       SimpleTexturedMaterialPtr tex = SimpleTexturedMaterial::create();
	        beginEditCP(tex);
		        tex->setImage( empty_image);
	        endEditCP(tex);
	        
	       
	        beginEditCP(geo, Geometry::TexCoordsFieldMask );

		        geo->setMaterial( tex );
		    
	        endEditCP(geo,  Geometry::TexCoordsFieldMask );
	        
	       
	        
         }
         
         
       glutPostRedisplay();   
 }
 
 
 
 NodePtr localModel (  UInt8* black_white_image_data_recived,  UInt32 width,  Pnt3f hit_point, bool event, float scale_value, Vec3f* P_recive , float angle_of_rotation)
{
        
        Vec3f min, max;
        osg::Matrix m1, m2, m3, m4, m5,m6, m7; 
        
        NodePtr model = OSG::SceneFileHandler::the().read("house1_3.3ds");/////defining the first model
	model->updateVolume();
	
		
	TransformPtr transform = Transform::create();                   ///applying transformation and rotaion and scaling first model//
	beginEditCP(transform, Transform::MatrixFieldMask );	        
                m1.setIdentity();
             
                if(event)       
                        m3.setTransform( Vec3f(hit_point[0], 0,  hit_point[2]),  Quaternion(Vec3f(1,0,0), -((90.0f * 3.14f) / 180.0f)));
		else
			m3.setTransform( Vec3f(hit_point[0], 0,  hit_point[2]),  Quaternion(Vec3f(1,0,0), -((90.0f * 3.14f) / 180.0f)));
                        

                m1.mult(m3);
                
               
                m4.setScale(scale_value,scale_value,scale_value);
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




        Vec3f center_of_bounding_box;
	
	center_of_bounding_box[0] = ((max[0] - min[0])/2.0);
	center_of_bounding_box[1] = ((max[1] - min[1])/2.0);
	center_of_bounding_box[2] = ((max[2] - min[2])/2.0);



  
                  /******placing the  model on the terrian*************/
	double area, lowestpoint=100000.0, variable;
	UInt32 x, z, j, i, length,breadth;
	double dx_left, dx_right, x_left, x_right, start_point, end_point;

	length = max[0] - min[0];                                           /////width//
	breadth = max[2] - min[2];                                          ////height///
	area = length * breadth;
      
	if( event)
	{
	        x = ( hit_point[0] ) - UInt32(length/2) ;
	        z = ( hit_point[2] ) - UInt32(breadth/2);
	
   
	}
	
	
	
	
	
	////the two for loops for checking the lowest point condition on the terrain
	////will scan the whole area where the model is going to be placed and then 
	////will place at the lowest point.
	
	if(event)
	{
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
	 }

	else
	{
		if(P_recive[0][2] == P_recive[1][2])
		{
			dx_left  = 0.0f;
			dx_right = 0.0f;
		}

		else
		{
			dx_left  = ( (P_recive[0][0] - P_recive[1][2]) / (P_recive[0][2] - P_recive[1][2]) );
			dx_right = ( (P_recive[0][0] - P_recive[3][2]) / (P_recive[0][2] - P_recive[3][2]) );
		}
		
		start_point = P_recive[0][2];
		end_point   = P_recive[2][2];

		x_left = x_right = P_recive[0][0];

		while( start_point <= end_point )
		{
			for( double k = x_left; k <= x_right; k = k + 1.0)
			{	
				variable = *(black_white_image_data_recived + (( UInt32(k) * (width) ) + UInt32(start_point))) * scale;
		
				if(lowestpoint > variable)
					lowestpoint = variable;
			}


			x_left  = x_left  + dx_left;
			x_right = x_right + dx_right;

			if(x_right == P_recive[3][0])
			{
				dx_right = ( (P_recive[3][0] - P_recive[2][0]) / (P_recive[3][2] - P_recive[2][2]) );
			}
			
			if(x_left == P_recive[1][0])
			{
				dx_left = ( (P_recive[1][0] - P_recive[2][0]) / (P_recive[1][2] - P_recive[2][2]) );
			}
			
			start_point = start_point + 1.0;
			
		}

	
	}
	
	
	//std::cout<<center_of_bounding_box<< std::endl;
	
	beginEditCP(transform, Transform::MatrixFieldMask );	        
                m1.setIdentity(); 
                
  
                 Vec3f trans,translate;
                

                 trans[0] = hit_point[0];
                 trans[1] = lowestpoint;
                 trans[2] = hit_point[2];
                 //std::cout<< "translate=" << translate << std::endl;
                 
                m1.setTranslate(0,0,0);                
                
                
                
                m3.setTransform( Quaternion( Vec3f( 1,0,0), -( ( 90.0f * 3.14f ) / 180.0f ))); 
                    
                m3.mult(m1);                
              
                m6.setTransform( Quaternion( Vec3f( 0,1,0), angle_of_rotation ));
                m6.mult(m3);

                
                m7.mult(m6);

                m7.setTranslate( trans );
                transform->setMatrix(m7);               

        endEditCP(transform, Transform::MatrixFieldMask );
          
	
	
        return transformNode;
      
}



////checking for the corner whetehr is blue or not
bool blue_check(  UInt32 z_variable ,  UInt32 x_variable , UInt8* image_data, UInt32 width_image)
{

        bool blue_point;
        if( image_data[(width_image * x_variable  * 4) + (z_variable  * 4) + 2] == 255)
		blue_point = true;                 


	else
		blue_point = false;
		

	return blue_point;
	
	
}


bool red_check( UInt32 z_variable ,  UInt32 x_variable , UInt8* image_data, UInt32 width_image)
{
	 bool red_point;
        if( image_data[(width_image * x_variable  * 3) + (z_variable  * 3) + 0] == 255)
		red_point = false;                 
	
	else
		red_point = true;

	return red_point;
}



 
 ////the function which is generalized which will check the case like whether any part is 
 ////a colour completly and will return a boolean value
 ////it will take the pointer of image and the width and the length and breadth of the model 
 
 bool check_condition(  UInt32 z_length,  UInt32  x_length,   UInt32 breadth,   UInt32 length,   UInt8* test_image_data,   UInt32 width_image, bool colour)
 {
        //checking for red
        
        bool not_adjacent = false, adjacent = false, not_blue = false, blue = false;
        
        //experimenting code
         if(colour)
        {
                 for( UInt32 j = z_length; j <= (z_length + breadth); j++ ) 
	         {
	                for( UInt32 i = x_length ; i <= (x_length + length); i++)
	                {
	
	                        if( test_image_data[(width_image * i  * 3) + (j  * 3) + 0] == 255)
                                         return false;

	
	                        else
                                         adjacent=true;
	                } 
  
	           } 

	           return true;
 
	  }
	  
	  
 	   else
	   {
	                    
                for( UInt32 j = z_length; j <= (z_length + breadth); j++ ) 
                {
                        for( UInt32 i = x_length ; i <= (x_length + length); i++)
                        {

                               if( test_image_data[(width_image * i  * 4) + (j  * 4) + 2] == 255)      //if ! blue
					blue = true;


                               else    // blue
					return false;


                        } 
           
                 } 
      
                  return true;
         
	   }
  
 
}


//////   colouring that part of terrain where the house is placed on the reference image
 void colouring_empty_terrain(UInt32 z_length,  UInt32  x_length,   UInt32 breadth,   UInt32 length,   UInt8* empty_image_data,   UInt32 width_housing_image, Vec3f* P_rec, bool inside)
 {
	double dx_left, dx_right, x_left, x_right, start_point, end_point;

 	if(inside)
	{	
        	for( UInt32 j = z_length; j <= (z_length + breadth); j++ ) 
	         {
	                for( UInt32 i = x_length ; i <= (x_length + length); i++)
	                {
                        //clouring that part of terrain where the model is been placed 
                        empty_image_data[(width_housing_image * i  * 3) + (j  * 3) + 0] = 255;
	                                                       
                	} 
        	}
	}

	else
	{
		if(P_rec[0][2] == P_rec[1][2])
		{
			dx_left  = 0.0f;
			dx_right = 0.0f;
		}

		else
		{
			dx_left  = ( (P_rec[0][0] - P_rec[1][2]) / (P_rec[0][2] - P_rec[1][2]) );
			dx_right = ( (P_rec[0][0] -P_rec[3][2]) / (P_rec[0][2] - P_rec[3][2]) );
		}
		
		start_point = P_rec[0][2];
		end_point   = P_rec[2][2];

		x_left = x_right = P_rec[0][0];

		while( start_point <= end_point )
		{
			for( double k = x_left; k <= x_right; k = k + 1.0)
			{	
				empty_image_data[(width_housing_image * (UInt32(start_point)  * 3) + (UInt32(k) * 3)) + 0] = 255;
			}

			
			x_left  = x_left  + dx_left;
			x_right = x_right + dx_right;

			if(x_right == P_rec[3][0])
			{
				dx_right = ( (P_rec[3][0] - P_rec[2][0]) / (P_rec[3][2] - P_rec[2][2]) );
			}
			
			if(x_left == P_rec[1][0])
			{
				dx_left = ( (P_rec[1][0] - P_rec[2][0]) / (P_rec[1][2] - P_rec[2][2]) );
			}
			
			start_point = start_point + 1.0;
			
		}
		
	}
 }





GroupNodePtr createScenegraph(void)
{

        

        /*********** defineing the texture image for texture mapping**********/
       
	colour_image = Image::create();
	colour_image -> read("colour_image.png");
	
	UInt32 width_colour_image   =  colour_image->getWidth();
	UInt32 height_colour_image  =  colour_image->getHeight();
	UInt8* colour_image_data    =  colour_image->getData();
	
		
	
	/*********** defineing the png  image for reading th evaluse from the image**********/
	black_white = Image::create();
	black_white -> read("black_white_image.pgm");	
        
	width  =  black_white->getWidth();	
	height =  black_white->getHeight();	
        black_white_image_data = black_white->getData();

	Real32 wHeight[width][height];
	
	/***************************taking a image which i same size of colour image************************/
	
	 housing_image = Image::create();
	housing_image -> read("housing.png");
	//housing_image -> read("housing_256.png");
	UInt32 width_housing_image   =  housing_image->getWidth();
	UInt32 height_housing_image  =  housing_image->getHeight();
	UInt8* housing_image_data  =  housing_image->getData();
	
	std::cout << width_housing_image<<std::endl;
	
	
	/****************************taking an empty image to use as reference***************************/
	
	
	empty_image       = Image::create();
	
	beginEditCP(empty_image);
	empty_image->set(Image::OSG_RGB_PF, width_housing_image, height_housing_image);
	endEditCP(empty_image);
	
	UInt8* empty_image_data    =  empty_image->getData();
	
	/**************************************************************************************************/

        /*****************************addding the image part ********************************************/
	SimpleTexturedMaterialPtr tex ;
	tex = SimpleTexturedMaterial::create();
	beginEditCP(tex);
		tex->setImage(colour_image);
	endEditCP(tex);


        /*************storing the image read data in the real32 wHeight*********************************/
	for(int i1=0; i1<height; i1++)
		for(int j=0; j<width; j++)
		{
			wHeight[i1][j] = black_white_image_data[((width*i1)+j)];
			
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
        geo = Geometry::create();
	beginEditCP(geo, Geometry::TypesFieldMask  |  Geometry::LengthsFieldMask | Geometry::IndicesFieldMask  |  Geometry::PositionsFieldMask | Geometry::TexCoordsFieldMask | Geometry::MaterialFieldMask );

		geo->setTypes( type );
		geo->setLengths( len );
		geo->setIndices( indices );
		geo->setPositions( pos );
		geo->setTexCoords( txt );
		geo->setMaterial( tex );
		geo->setDlistCache( false );
               
	endEditCP(geo, Geometry::TypesFieldMask | Geometry::LengthsFieldMask  |  Geometry::IndicesFieldMask  |  Geometry::PositionsFieldMask  | Geometry::TexCoordsFieldMask | Geometry::MaterialFieldMask );

	calcVertexNormals(geo);


        NodePtr geonode = makeNodeFor(geo);                             ///////////making the main node for the geometry//////////////////////////////
        
        geonode->getToWorld(geometrymatrix);                            /////////////getting the geometry matrix//////////
        
        
        
        
        
        float scale_value = 1.0;
        osg::Matrix m1, m2, m3, m4, m5, final_matrix;	
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
	  
	Pnt3f placing_point ,first_corner, fourth_corner, third_corner, second_corner ;
	
	
	Vec3f p[4];
	UInt32  length,breadth;
	
	length = static_cast<int>(max[0] - min[0]);        // should be ceiled                /////width//
	breadth = static_cast<int>(max[2] - min[2]);                                          ///height///
	
        bool inside = false, not_adjacent= false, adjacent = false, outside = false, event = 0, one = true;	
        
        UInt32 l = length/2;
        UInt32 b = breadth/2;
        UInt32 breadth_variable, width_variable;
         
        double angle_of_rotation = 0.0;
         
        /// scanning a image to find whether the area is of a particular colour or not and 
        /// then if the whole are is of that colour then the model is being placed with the boundary condtions of the 
        /// colour.
        for( width_variable = l;   width_variable < width_housing_image - l;   width_variable++)
        {
	        for( breadth_variable = b;   breadth_variable < height_housing_image - b;   breadth_variable++)
	        {     
	        
	                 
	                //checking initially for the co-ordinates whether that co-ordinates has the blue colour so as to place the model          
	                if(  housing_image_data[(width_housing_image * width_variable * 4) + (breadth_variable * 4) + 2] == 255)
	                        {
	                               
	                               
	                               
	                                /// finding the initial cordinates of the model so as to scann the complete area
	                                UInt32 x_length = ( width_variable ) -(l);
	                                UInt32 z_length = ( breadth_variable ) - (b);  
	                              
	                              //outputFile<<"breadth_variable = "<<breadth_variable<<std::endl;
	                              
	                              
	                              
	                             
	                                //outputFile<<"checking for red"<<std::endl;
	                                
	                                //// looking whether a model is already there so as to check the if other nodel is placed it does not overlap any other model
	                                bool not_red = check_condition(z_length, x_length, breadth, length, empty_image_data, width_housing_image, true);   
	                                        
	                             

	                                   
	                                ////now checking the condtion whether the area where the model has to be placed is of desired colour or not
	                                bool  blue = check_condition(z_length, x_length, breadth, length, housing_image_data, width_housing_image, false);
	                                         
	                                       
					
	

	                               if(blue == false)
	                                        {
 							
						        placing_point[0] = width_variable;
	                                                placing_point[1] = 0;
	                                                placing_point[2] = breadth_variable;
							
							outputFile<<"placing_point = "<<placing_point<<std::endl;
                                                        float ang = 10.0f,min_x, max_x, min_z, max_z;
                                                        int times=1;
							bool blue_point, red_point, p1_blue, p2_blue, p3_blue, p4_blue;

							double dx_left, dx_right, x_left, x_right, start_point, end_point;

								
 							for(; ang <= 90.0f; ang = ang +10.0f)
							{
							        outputFile<<"times = "<<times<<std::endl;
								angle_of_rotation =   ang ;
								
								first_corner[0] = x_length;			first_corner[1] = 0;                first_corner[2] =z_length;
								
                                         			outputFile<<"point first bfeor rotation="<<first_corner<<std::endl;
                                                                        
								second_corner[0] = (x_length + length);		second_corner[1] = 0;               second_corner[2] = z_length;
                                         			outputFile<<"point second before rotation="<<second_corner<<std::endl;
                                                                        
								third_corner[0] = (x_length + length);		third_corner[1] = 0;		    third_corner[2] =(z_length + breadth);
                                         			outputFile<<"point third before rotation="<<third_corner<<std::endl;
                                                                        
								fourth_corner[0] = x_length;			fourth_corner[1] = 0;               fourth_corner[2] =(z_length + breadth);
                                         			outputFile<<"point fourth before rotation="<<fourth_corner<<std::endl;




								//caling the function to rotate the house and then returi=ning the rtated matrix
								final_matrix = rotation (  black_white_image_data,  width,   placing_point , angle_of_rotation, 1.0);
								outputFile<<"final_matrix="<<final_matrix<<std::endl;
								//multiplying the four corner of the house to get the new rotated corner of the house
								final_matrix.mult( first_corner);
								outputFile<<"point first p1="<<first_corner<<std::endl;

								final_matrix.mult( second_corner);
								outputFile<<"point second p2="<<second_corner<<std::endl;

								final_matrix.mult( third_corner);
								outputFile<<"point third p3="<<third_corner<<std::endl;

								final_matrix.mult( fourth_corner);
								outputFile<<"point fourth p4="<<fourth_corner<<std::endl;
								
								
								
								////calculating the minimum values and maximum valuse 
								////assigning the minimum value of x to point p1 and maximum value of x to point p3 from the four corners
								////assigning the minimum value of z to point p2 and maximum value of z to point p4 from the four corners

								////calculating the minimum value of x and maximum value of x and assigning the mininum value to point p1 and maximu value to point p3.
								min_x = first_corner[0];
								p[0]  = first_corner;
								p[2]  = third_corner;
								
								////calculating the minimum value of x and assigning the mininum value to point p1
								//minimum value of the x from the four corners
								if(min_x > second_corner[0])
								{
								        min_x = second_corner[0];
								        p[0]  =  second_corner;
									p[2] =   fourth_corner;
								}
								
								if(min_x > third_corner[0])
								{
									min_x = third_corner[0];
									p[0]  = third_corner;
									p[2] =  first_corner;
								}

								if(min_x > fourth_corner[0])
								{
									min_x = fourth_corner[0];
									p[0]  = fourth_corner;
									p[2]  = second_corner;
							        }
								

								////calculating the minimum value of z and maximum value of z and assigning the mininum value to point p2 and maximu value to point p4.
								////calculating the minimum value of z and maximum value of z.
								min_z = first_corner[2];
								p[1] = first_corner;
								p[3] = third_corner;
								
								////calculating the minimum value of z assigning the mininum value to point p2
                                                                //minimum value of the z from the four corners
								if(min_z > second_corner[2])
								{
								        min_z = second_corner[2];
								        p[1]  = second_corner;
									p[3]  = fourth_corner;
								}
								
								if(min_z > third_corner[2])
								{
									min_z = third_corner[2];
									p[1]  = third_corner;
									p[3]  = first_corner;
								}

								if(min_z > fourth_corner[2])
								{
									min_z = fourth_corner[2];
									p[1]  = fourth_corner;
									p[3]  = second_corner;
								}
	
								outputFile<<"p[0]="<<p[0]<<std::endl;
								outputFile<<"p[1]="<<p[1]<<std::endl;
								outputFile<<"p[2]="<<p[2]<<std::endl;
								outputFile<<"p[3]="<<p[3]<<std::endl;
								////checking whether the four corners are within the blue patch or not
								p1_blue = blue_check(  p[0][2] ,  p[0][0] ,  housing_image_data, width_housing_image);
								p2_blue = blue_check(  p[1][2] ,  p[1][0] ,  housing_image_data, width_housing_image);	
								p3_blue = blue_check(  p[2][2] ,  p[2][0] ,  housing_image_data, width_housing_image);	
								p4_blue = blue_check(  p[3][2] ,  p[3][0] ,  housing_image_data, width_housing_image);	\
								
								outputFile<<"p1="<<p1_blue<<std::endl;
								outputFile<<"p2="<<p2_blue<<std::endl;
								outputFile<<"p3="<<p3_blue<<std::endl;
								outputFile<<"p4="<<p4_blue<<std::endl;

								if(p1_blue && p2_blue && p3_blue && p4_blue )
								{	
									outputFile<<"all one corner blue"<<std::endl;
									if(p[0][2] == p[1][2])
									{
										dx_left  = 0.0f;
										dx_right = 0.0f;
									}
	
									else
									{
										dx_left  = ( (p[0][0] - p[1][2]) / (p[0][2] - p[1][2]) );
										dx_right = ( (p[0][0] - p[3][2]) / (p[0][2] - p[3][2]) );
									}
									
									start_point = p[0][2];
									end_point   = p[2][2];
	
									x_left = x_right = p[0][0];
	
									while( start_point <= end_point )
									{
										for( double k = x_left; k <= x_right; k = k + 1.0)
										{	
											blue_point = blue_check( k, start_point, housing_image_data, width_housing_image);
											if(blue_point)
											{	
												red_point = red_check( k, start_point, empty_image_data, width_housing_image);
											}
											else
												break;
											
											if((blue_point == false) || (red_point == true))
												break;
										}

										if((blue_point == false) || (red_point == true))
												break;

										x_left  = x_left  + dx_left;
										x_right = x_right + dx_right;

										if(x_right == p[3][0])
										{
											dx_right = ( (p[3][0] - p[2][0]) / (p[3][2] - p[2][2]) );
										}
										
										if(x_left == p[1][0])
										{
											dx_left = ( (p[1][0] - p[2][0]) / (p[1][2] - p[2][2]) );
										}
										
										start_point = start_point + 1.0;
										
									}
	
	
	
									if( blue_point == true && red_point == false)
									{
										
										
										if(width_housing_image == 256)
										{
								
											placing_point[0] = width_variable / (float)height_housing_image * height_colour_image;
											placing_point[1] = 0;
											placing_point[2] = breadth_variable / (float)width_housing_image * width_colour_image;
											
	
	
											NodePtr SourceNode = localModel( black_white_image_data, width,  placing_point, 0, (width_colour_image / (float)width_housing_image), p,  angle_of_rotation); 
		
											localRoots.push_back(SourceNode);
										}
		
										else
										{
											placing_point[0] = width_variable;
											placing_point[1] = 0;
											placing_point[2] = breadth_variable;
											
	
											
											///calling the function //////////////
											NodePtr SourceNode = localModel( black_white_image_data, width, placing_point, 0, 1.0, p, angle_of_rotation); 
	
												localRoots.push_back(SourceNode);
										}
										
										
										colouring_empty_terrain(z_length, x_length, breadth, length, empty_image_data, width_housing_image, p, 0);
										
										
									}
									//outputFile<<"changed firstcorner="<<first_corner<<std::endl;
								}
							        times =  times+1;
							}
							
							
                                                }
	
	
	
	
	                                ///if satisfying both the conditions like whetehr the area is blue and no other model is been there so that the model to be placed does not overlap
	                                if( (blue == true) && (not_red == true ))
	                                {
	 
	
	
	                                        if(width_housing_image == 256)
	                                        {
							
	                                                placing_point[0] = width_variable / (float)height_housing_image * height_colour_image;
	                                                placing_point[1] = 0;
	                                                placing_point[2] = breadth_variable / (float)width_housing_image * width_colour_image;
	
	                                                NodePtr SourceNode = localModel( black_white_image_data, width,  placing_point, 1,( width_colour_image / (float)width_housing_image), 0,0.0); 
	 
	                                                                localRoots.push_back(SourceNode);
	                                        }
	 



	                                        else
	                                        {
	                                                placing_point[0] = width_variable;
	                                                placing_point[1] = 0;
	                                                placing_point[2] = breadth_variable;

	                                                NodePtr SourceNode = localModel( black_white_image_data, width, placing_point, 1, 1.0, 0, 0.0);        ////calling the function //////////////

                                                                        localRoots.push_back(SourceNode);
                                                }


                                                colouring_empty_terrain(z_length, x_length, breadth, length, empty_image_data, width_housing_image, 0, 1);
	

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


osg::Matrix rotation (  UInt8* black_white_image_data_recived,  UInt32 width,  Pnt3f hit_point, float angle_of_rotation, float scale_value)
{

        Vec3f min, max;
        osg::Matrix m1, m2, m3, m4, m5,m6, m7, rotated_matrix; 
        
        NodePtr model = OSG::SceneFileHandler::the().read("house1_3.3ds");/////defining the first model
	model->updateVolume();
	
		
	TransformPtr transform = Transform::create();                   ///applying transformation and rotaion and scaling first model//
	beginEditCP(transform, Transform::MatrixFieldMask );	        
                m1.setIdentity();

                m3.setTransform( Vec3f(hit_point[0], 0,  hit_point[2]),  Quaternion(Vec3f(1,0,0), -((90.0f * 3.14f) / 180.0f)));

                m1.mult(m3);
 
                m4.setScale(scale_value,scale_value,scale_value);
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


	Vec3f center_of_bounding_box;
	
	center_of_bounding_box[0] = ((max[0] - min[0])/2.0);
	center_of_bounding_box[1] = ((max[1] - min[1])/2.0);
	center_of_bounding_box[2] = ((max[2] - min[2])/2.0);


                  /******placing the  model on the terrian*************/
	
	outputFile<<"hit_point ="<<hit_point<<std::endl;

	beginEditCP(transform, Transform::MatrixFieldMask );	        
                m1.setIdentity(); 

  
                Vec3f trans;

		///defineing the trans vector to the hit point and 
                 trans[0] = hit_point[0];
                 trans[1] = 0;
                 trans[2] = hit_point[2];
                 //std::cout<< "translate=" << translate << std::endl;
 
                m1.setTranslate(0,0,0);                
 		

                ///intial rotaion along x axis to make house up right down on the terrain
                m3.setTransform( Quaternion( Vec3f( 1,0,0), -( 90.0f ))); 
		//outputFile<<"m3 ="<<m3<<std::endl; 
                m3.mult(m1);

		///roatating the house around y axis 
                m6.setTransform( Quaternion( Vec3f( 0,1,0), (angle_of_rotation) ));
		//outputFile<<"m6 ="<<m6<<std::endl; 
                m6.mult(m3);
		//outputFile<<"m6 ="<<m6<<std::endl; 

                
		
                m7.setTranslate( trans );
		m7.mult(m6);
                transform->setMatrix(m7);               

        endEditCP(transform, Transform::MatrixFieldMask );


	

        outputFile<<"m7 ="<<m7<<std::endl; 
        return m7;

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
