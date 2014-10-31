/*
 * Final Project: Star Wars IV Death Star Trench Scene
 * Christopher Jordan and Jeremy Granger
 * CSCI 4229 Fall 2014
 *
 *
 *  Key bindings:
 */
#include "CSCIx229.h"
#include <time.h>

// World variables
int mode=0;       //  Texture mode
int view=1;       //  Projection mode
int move=0;       //  Move light
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
double asp=1;     //  Aspect ratio
double dim=30.0;   //  Size of world

// Texture array
unsigned int texture[10]; // Texture names

// Light values
int one       =   1;  // Unit value
int distance  =  15;  // Light distance
int inc       =  10;  // Ball increment
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model
int emission  =   0;  // Emission intensity (%)
int ambient   =  30;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shinyvec[1];    // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   0;  // Elevation of light

// For idle function
unsigned long ot;
unsigned long dt;

// For initclock
int first=0;

/*
 *  Determine normal for triangle using the first point as
 *  an origin for the vectors that go to points 2 and 3
 *     
 */
 static void normal(double x1, double y1, double z1,
                  double x2, double y2, double z2,
                  double x3, double y3, double z3){
   // Build first vector
   double v1x = x2 - x1;
   double v1y = y2 - y1;
   double v1z = z2 - z1;

   // Build second vector
   double v2x = x3 - x1;
   double v2y = y3 - y1;
   double v2z = z3 - z1;

   // Get Cross Product
   double nx = (v1y*v2z) - (v1z*v2y);
   double ny = (v1z*v2x) - (v1x*v2z);
   double nz = (v1x*v2y) - (v1y*v2x);

   // Set normal for trianlge plane
   glNormal3f(nx,ny,nz);
 }

/*
 *  Draw an x-wing wing laser cannon
 *     
 */
static void wingLaser(double x, double y, double z){
   int th = 0;

   glPushMatrix();
   glTranslated(x, y, z);

   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_TRIANGLE_FAN);
   glVertex3d(0, 0, 0);
   for (th = 0; th <= 360; th += 5)
   {
      glNormal3d(0,0,-1);
      glTexCoord2f(0.1558 + 0.5 * Cos(th), 0.25 + 0.5 * Sin(th)); glVertex3d(0.5 * Cos(th), 0.5 * Sin(th), 0);
      
   }
   glEnd();

   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_QUAD_STRIP);
   for (th = 0; th <= 360; th += 5)
   {
      glNormal3d(Cos(th),Sin(th),0);
      glTexCoord2f(0,th*0.00274); glVertex3d(0.5 * Cos(th), 0.5 * Sin(th), 0);
      glTexCoord2f(1,th*0.00274); glVertex3d(0.5 * Cos(th), 0.5 * Sin(th), 1);
   }
   glEnd();

   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_TRIANGLE_FAN);
   glVertex3d(0, 0, 1);
   for (th = 0; th <= 360; th += 5)
   {
      glNormal3d(0,0,-1);
      glTexCoord2f(0.2182 + 0.7 * Cos(th), 0.35 + 0.7 * Sin(th)); glVertex3d(0.7 * Cos(th), 0.7 * Sin(th), 1);
      
   }
   glEnd();
   
   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_TRIANGLE_FAN);
   glVertex3d(0, 0, 8);
   for (th = 0; th <= 360; th += 5)
   {
      glNormal3d(0,0,1);
      glTexCoord2f(0.2182 + 0.7 * Cos(th), 0.35 + 0.7 * Sin(th)); glVertex3d(0.7 * Cos(th), 0.7 * Sin(th), 8);
      
   }
   glEnd();
   
   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_QUAD_STRIP);
   for (th = 0; th <= 360; th += 5)
   {
      glNormal3d(Cos(th),Sin(th),0);
      glTexCoord2f(0,th*0.00274); glVertex3d(0.7 * Cos(th), 0.7 * Sin(th), 1);
      glTexCoord2f(1,th*0.00274); glVertex3d(0.7 * Cos(th), 0.7 * Sin(th), 8);
   }
   glEnd();

   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_TRIANGLE_FAN);
   glVertex3d(0, 0, 16);
   for (th = 0; th <= 360; th += 5)
   {
      glNormal3d(0,0,1);
      glTexCoord2f(0.1247 + 0.4 * Cos(th), 0.2 + 0.4 * Sin(th)); glVertex3d(0.4 * Cos(th), 0.4 * Sin(th), 16);
      
   }
   glEnd();

   glBindTexture(GL_TEXTURE_2D,texture[7]);
   glBegin(GL_QUAD_STRIP);
   for (th = 0; th <= 360; th += 5)
   {
      glNormal3d(Cos(th),Sin(th),0);
      glTexCoord2f(0,th*0.00274); glVertex3d(0.4 * Cos(th), 0.4 * Sin(th), 8);
      glTexCoord2f(1,th*0.00274); glVertex3d(0.4 * Cos(th), 0.4 * Sin(th), 16);
   }
   glEnd();

   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_TRIANGLE_FAN);
   glVertex3d(0, 0, 24);
   for (th = 0; th <= 360; th += 5)
   {
      glNormal3d(0,0,1);
      glTexCoord2f(0.08 + 0.25 * Cos(th), 0.1875 + 0.25 * Sin(th)); glVertex3d(0.25 * Cos(th), 0.25 * Sin(th), 24);
      
   }
   glEnd();

   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_QUAD_STRIP);
   for (th = 0; th <= 360; th += 5)
   {
      glNormal3d(Cos(th),Sin(th),0);
      glTexCoord2f(0,th*0.00274); glVertex3d(0.25 * Cos(th), 0.25 * Sin(th), 16);
      glTexCoord2f(1,th*0.00274); glVertex3d(0.25 * Cos(th), 0.25 * Sin(th), 24);
   }
   glEnd();

   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_TRIANGLE_FAN);
   glVertex3d(0, 0, 24.5);
   for (th = 0; th <= 360; th += 5)
   {
      glNormal3d(0,0,1);
      glTexCoord2f(0.256 + 0.8 * Cos(th), 0.6 + 0.8 * Sin(th)); glVertex3d(0.8 * Cos(th), 0.8 * Sin(th), 24.5);
      
   }
   glEnd();

   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_QUAD_STRIP);
   for (th = 0; th <= 360; th += 5)
   {
      glNormal3d(Cos(th),Sin(th),0);
      glTexCoord2f(0,th*0.00274); glVertex3d(0.4 * Cos(th), 0.4 * Sin(th), 24);
      glTexCoord2f(1,th*0.00274); glVertex3d(0.4 * Cos(th), 0.4 * Sin(th), 24.5);
   }
   glEnd();

   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_TRIANGLE_FAN);
   glVertex3d(0, 0, 26);
   for (th = 0; th <= 360; th += 5)
   {
      glNormal3d(0,0,1);
      glTexCoord2f(0.032 + 0.1 * Cos(th), 0.075 + 0.1 * Sin(th)); glVertex3d(0.1 * Cos(th), 0.1 * Sin(th), 26);
      
   }
   glEnd();

   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_QUAD_STRIP);
   for (th = 0; th <= 360; th += 5)
   {
      glNormal3d(Cos(th),Sin(th),0);
      glTexCoord2f(0,th*0.00274); glVertex3d(0.1 * Cos(th), 0.1 * Sin(th), 24.5);
      glTexCoord2f(1,th*0.00274); glVertex3d(0.1 * Cos(th), 0.1 * Sin(th), 26);
   }
   glEnd();

   glPopMatrix();
}

/*
 *  Draw an x-wing wing engine
 *     
 */
static void wingEngine(double x, double y, double z){
   int th = 0;
   glPushMatrix();
   glTranslated(x, y, z);

   glBindTexture(GL_TEXTURE_2D,texture[4]);
   glBegin(GL_TRIANGLE_FAN);
   glVertex3d(0, 0, 0);
   for (th = 0; th <= 360; th += 1)
   {
      glNormal3d(0,0,-1);
      glTexCoord2f(0.25 + 0.1 * Cos(th), 0.5 + 0.1 * Sin(th)); glVertex3d(1.5 * Cos(th), 1.5 * Sin(th), 0);
      
   }
   glEnd();
   
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_TRIANGLE_FAN);
   glVertex3d(0, 0, 8);
   for (th = 0; th <= 360; th += 1)
   {
      glNormal3d(0,0,1);
      glTexCoord2f(0.5 + Cos(th), 0.5 + Sin(th)); glVertex3d(1.5 * Cos(th), 1.5 * Sin(th), 8);
      
   }
   glEnd();
   
   glBindTexture(GL_TEXTURE_2D,texture[4]);
   glBegin(GL_QUAD_STRIP);
   for (th = 0; th <= 360; th += 1)
   {
      glNormal3d(Cos(th),Sin(th),0);
      glTexCoord2f(0,th*0.0016); glVertex3d(1.5 * Cos(th), 1.5 * Sin(th), 0);
      glTexCoord2f(1,th*0.0016); glVertex3d(1.5 * Cos(th), 1.5 * Sin(th), 8);
   }
   glEnd();

   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_TRIANGLE_FAN);
   glVertex3d(0, 0, -9);
   for (th = 0; th <= 360; th += 1)
   {
      glNormal3d(0,0,-1);
      glTexCoord2f(0.5 + Cos(th), 0.5 + Sin(th)); glVertex3d(0.8 * Cos(th), 0.8 * Sin(th), -9);
      
   }
   glEnd();

   glBindTexture(GL_TEXTURE_2D,texture[4]);
   glBegin(GL_QUAD_STRIP);
   for (th = 0; th <= 360; th += 1)
   {
      glNormal3d(Cos(th),Sin(th),0);
      glTexCoord2f(0,th*0.0016); glVertex3d(.8 * Cos(th), 0.8 * Sin(th), 0);
      glTexCoord2f(1,th*0.0016); glVertex3d(.8 * Cos(th), 0.8 * Sin(th), -9);
   }
   glEnd();
   glPopMatrix();
}

/*
 *  Draw the upper wing of the x-wing
 *     
 */
static void createWings(){
   // ------------------- Left Top Wing -----------------------------------
   // Bottom of wing
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_POLYGON);
   normal(-3,0.5,-17, -3,0.5,-7, -25,8,-14);
   glTexCoord2f(1,0); glVertex3d(-3,+0.5,-7);
   glTexCoord2f(1,0.9031); glVertex3d(-3,+0.5,-17);
   glTexCoord2f(0,0.6217); glVertex3d(-25,+8,-14);
   glTexCoord2f(0,0.2709); glVertex3d(-25,+8,-10);
   glEnd();

   // Top of wing
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_POLYGON);
   normal(-3,1.5,-17, -25,9,-14, -3,1.5,-7);
   glTexCoord2f(1,0); glVertex3d(-3,+1.5,-7);
   glTexCoord2f(1,0.9031); glVertex3d(-3,+1.5,-17);
   glTexCoord2f(0,0.6217); glVertex3d(-25,+9,-14);
   glTexCoord2f(0,0.2709); glVertex3d(-25,+9,-10);
   glEnd();

   // Wing front side
   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_POLYGON);
   normal(-25,8,-10, -25,9,-10, -3,0.5,-7);
   glTexCoord2f(0,0.1); glVertex3d(-3,+0.5,-7);
   glTexCoord2f(1,0.1); glVertex3d(-25,+8,-10);
   glTexCoord2f(1,0.1729); glVertex3d(-25,+9,-10);
   glTexCoord2f(0,0.1729); glVertex3d(-3,+1.5,-7);
   glEnd();

   // Wing back side
   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_POLYGON);
   normal(-25,8,-14, -3,0.5,-17, -25,9,-14);
   glTexCoord2f(1,0.1); glVertex3d(-3,+0.5,-17);
   glTexCoord2f(0,0.1); glVertex3d(-25,+8,-14);
   glTexCoord2f(0,0.1729); glVertex3d(-25,+9,-14);
   glTexCoord2f(1,0.1729); glVertex3d(-3,+1.5,-17);
   glEnd();

   // Wing end cap
   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_POLYGON);
   normal(-25,8,-14, -25,9,-14, -25,8,-10);
   glTexCoord2f(0,0.5011); glVertex3d(-25,+9,-14);
   glTexCoord2f(0,0.1); glVertex3d(-25,+8,-14);
   glTexCoord2f(1,0.1); glVertex3d(-25,+8,-10);
   glTexCoord2f(1,0.5011); glVertex3d(-25,+9,-10);
   glEnd();

   // Upper Left Engine and Laser
   wingEngine(-5.4, 3.75, -13);
   wingLaser(-24, 9, -16);

   // ------------------- Left Bottom Wing -----------------------------------
   // Top of wing
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_POLYGON);
   normal(-3,0.5,-17, -25,-7,-14, -3,0.5,-7);
   glTexCoord2f(1,0); glVertex3d(-3,+0.5,-7);
   glTexCoord2f(1,0.9031); glVertex3d(-3,+0.5,-17);
   glTexCoord2f(0,0.6217); glVertex3d(-25,-7,-14);
   glTexCoord2f(0,0.2709); glVertex3d(-25,-7,-10);
   glEnd();

   // Bottom of wing
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_POLYGON);
   normal(-3,-0.5,-17, -3,-0.5,-7, -25,-8,-14);
   glTexCoord2f(1,0); glVertex3d(-3,-0.5,-7);
   glTexCoord2f(1,0.9031); glVertex3d(-3,-0.5,-17);
   glTexCoord2f(0,0.6217); glVertex3d(-25,-8,-14);
   glTexCoord2f(0,0.2709); glVertex3d(-25,-8,-10);
   glEnd();

   // Wing front side
   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_POLYGON);
   normal(-25,-7,-10, -25,-8,-10, -3,0.5,-7);
   glTexCoord2f(0,0.1); glVertex3d(-3,+0.5,-7);
   glTexCoord2f(1,0.1); glVertex3d(-25,-7,-10);
   glTexCoord2f(1,0.1729); glVertex3d(-25,-8,-10);
   glTexCoord2f(0,0.1729); glVertex3d(-3,-0.5,-7);
   glEnd();

   // Wing back side
   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_POLYGON);
   normal(-25,-7,-14, -3,0.5,-17, -25,-8,-14);
   glTexCoord2f(1,0.1); glVertex3d(-3,+0.5,-17);
   glTexCoord2f(0,0.1); glVertex3d(-25,-7,-14);
   glTexCoord2f(0,0.1729); glVertex3d(-25,-8,-14);
   glTexCoord2f(1,0.1729); glVertex3d(-3,-0.5,-17);
   glEnd();

   // Wing end cap
   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_POLYGON);
   normal(-25,-7,-14, -25,-8,-14, -25,-7,-10);
   glTexCoord2f(0,0.5011); glVertex3d(-25,-8,-14);
   glTexCoord2f(0,0.1); glVertex3d(-25,-7,-14);
   glTexCoord2f(1,0.1); glVertex3d(-25,-7,-10);
   glTexCoord2f(1,0.5011); glVertex3d(-25,-8,-10);
   glEnd();

   // Bottom Left Engine and Laser
   wingEngine(-5.4, -2.3, -13);
   wingLaser(-24, -8, -16);

   // ------------------- Right Top Wing -----------------------------------
   // Bottom of wing
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_POLYGON);
   normal(3,0.5,-17, 25,8,-14, 3,0.5,-7);
   glTexCoord2f(1,0); glVertex3d(+3,+0.5,-7);
   glTexCoord2f(1,0.9031); glVertex3d(+3,+0.5,-17);
   glTexCoord2f(0,0.6217); glVertex3d(+25,+8,-14);
   glTexCoord2f(0,0.2709); glVertex3d(+25,+8,-10);
   glEnd();

   // Top of wing
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_POLYGON);
   normal(3,1.5,-17, 3,1.5,-7, 25,9,-14);
   glTexCoord2f(1,0); glVertex3d(+3,+1.5,-7);
   glTexCoord2f(1,0.9031); glVertex3d(+3,+1.5,-17);
   glTexCoord2f(0,0.6217); glVertex3d(+25,+9,-14);
   glTexCoord2f(0,0.2709); glVertex3d(+25,+9,-10);
   glEnd();

   // Front wing side
   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_POLYGON);
   normal(25,8,-10, 25,9,-10, 3,0.5,-7);
   glTexCoord2f(0,0.1); glVertex3d(+3,+0.5,-7);
   glTexCoord2f(1,0.1); glVertex3d(+25,+8,-10);
   glTexCoord2f(1,0.1729); glVertex3d(+25,+9,-10);
   glTexCoord2f(0,0.1729); glVertex3d(+3,+1.5,-7);
   glEnd();

   // Back wing side
   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_POLYGON);
   normal(+25,8,-14, +3,0.5,-17, +25,9,-14);
   glTexCoord2f(1,0.1); glVertex3d(-+3,+0.5,-17);
   glTexCoord2f(0,0.1); glVertex3d(+25,+8,-14);
   glTexCoord2f(0,0.1729); glVertex3d(+25,+9,-14);
   glTexCoord2f(1,0.1729); glVertex3d(+3,+1.5,-17);
   glEnd();

   // Wing end cap
   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_POLYGON);
   normal(25,8,-14, 25,9,-14, 25,8,-10);
   glTexCoord2f(0,0.5011); glVertex3d(+25,+9,-14);
   glTexCoord2f(0,0.1); glVertex3d(+25,+8,-14);
   glTexCoord2f(1,0.1); glVertex3d(+25,+8,-10);
   glTexCoord2f(1,0.5011); glVertex3d(+25,+9,-10);
   glEnd();

   // Upper Right Engine and Laser
   wingEngine(5.4, 3.75, -13);
   wingLaser(24, 9, -16);

   // ------------------- Right Bottom Wing -----------------------------------
   // Top of wing
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_POLYGON);
   normal(3,0.5,-17, 3,0.5,-7, 25,-7,-14);
   glTexCoord2f(1,0); glVertex3d(+3,+0.5,-7);
   glTexCoord2f(1,0.9031); glVertex3d(+3,+0.5,-17);
   glTexCoord2f(0,0.6217); glVertex3d(+25,-7,-14);
   glTexCoord2f(0,0.2709); glVertex3d(+25,-7,-10);
   glEnd();

   // Bottom of wing
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_POLYGON);
   normal(3,-0.5,-17, 25,-8,-14, 3,-0.5,-7);
   glTexCoord2f(1,0); glVertex3d(+3,-0.5,-7);
   glTexCoord2f(1,0.9031); glVertex3d(+3,-0.5,-17);
   glTexCoord2f(0,0.6217); glVertex3d(+25,-8,-14);
   glTexCoord2f(0,0.2709); glVertex3d(+25,-8,-10);
   glEnd();

   // Wing front side
   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_POLYGON);
   normal(25,-7,-10, 3,0.5,-7, 25,-8,-10);
   glTexCoord2f(0,0.1); glVertex3d(+3,+0.5,-7);
   glTexCoord2f(1,0.1); glVertex3d(+25,-7,-10);
   glTexCoord2f(1,0.1729); glVertex3d(+25,-8,-10);
   glTexCoord2f(0,0.1729); glVertex3d(+3,-0.5,-7);
   glEnd();

   // Wing back side
   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_POLYGON);
   normal(25,-7,-14, 25,-8,-14, 3,0.5,-17);
   glTexCoord2f(1,0.1); glVertex3d(+3,+0.5,-17);
   glTexCoord2f(0,0.1); glVertex3d(+25,-7,-14);
   glTexCoord2f(0,0.1729); glVertex3d(+25,-8,-14);
   glTexCoord2f(1,0.1729); glVertex3d(+3,-0.5,-17);
   glEnd();

   // Wing end cap
   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_POLYGON);
   normal(25,-7,-14, 25,-7,-10, 25,-8,-14);
   glTexCoord2f(0,0.5011); glVertex3d(+25,-8,-14);
   glTexCoord2f(0,0.1); glVertex3d(+25,-7,-14);
   glTexCoord2f(1,0.1); glVertex3d(+25,-7,-10);
   glTexCoord2f(1,0.5011); glVertex3d(+25,-8,-10);
   glEnd();

   // Bottom Right Engine and Laser
   wingEngine(5.4, -2.3, -13);
   wingLaser(24, -8, -16);
}

/*
 *  Draw an x-wing
 *     
 */
static void xWing(double x, double y, double z,
                 double dx, double dy, double dz,
                 double rx, double ry, double rz,
                 double th)
{
   //  Save transformation
   glPushMatrix();
   
   //  Offset
   glTranslated(x,y,z);
   glScaled(dx,dy,dz);
   glRotated(th,rx,ry,rz);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);

   // Nose left top panel
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_POLYGON);
   glColor3f(0.75,0.75,0.75);
   normal(-5,0,-3, -2,0,25, -1,1.5,30);
   glTexCoord2f(-1,-1); glVertex3d(-5,+0,-3);
   glTexCoord2f(-1,1); glVertex3d(-2,+0,+30);
   glTexCoord2f(0,1); glVertex3d(-1,+1.5,+30);
   glTexCoord2f(1,1); glVertex3d(-2,+2.5,+7);
   glTexCoord2f(1,0); glVertex3d(-3,+5,+0);
   glTexCoord2f(1,0); glVertex3d(-3,+5,-2);
   glTexCoord2f(-1,1); glVertex3d(-3,+4,-3);
   glEnd();

   // Nose right top panel
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_POLYGON);
   normal(5,0,-3, 2,0,25, 1,1.5,30);
   glTexCoord2f(-1,-1); glVertex3d(+5,+0,-3);
   glTexCoord2f(-1,1); glVertex3d(+2,+0,+30);
   glTexCoord2f(0,1); glVertex3d(+1,+1.5,+30);
   glTexCoord2f(1,1); glVertex3d(+2,+2.5,+7);
   glTexCoord2f(1,0); glVertex3d(+3,+5,+0);
   glTexCoord2f(1,0); glVertex3d(+3,+5,-2);
   glTexCoord2f(-1,1); glVertex3d(+3,+4,-3);
   glEnd();

   // Cockpit window panel
   glBindTexture(GL_TEXTURE_2D,texture[8]);
   glBegin(GL_POLYGON);
   normal(3,5,0, -3,5,0, -2,2.5,7);
   glTexCoord2f(0,1); glVertex3d(+3,+5,+0);
   glTexCoord2f(1,0); glVertex3d(-3,+5,+0);
   glTexCoord2f(-1,0); glVertex3d(-2,+2.5,+7);
   glTexCoord2f(0,-1); glVertex3d(+2,+2.5,+7);
   glEnd();

   // Cockpit top panel
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_POLYGON);
   normal(3,5,0, -3,5,-2, -3,5,0);
   glTexCoord2f(1,0); glVertex3d(+3,+5,+0);
   glTexCoord2f(0,0); glVertex3d(-3,+5,+0);
   glTexCoord2f(0,1); glVertex3d(-3,+5,-2);
   glTexCoord2f(1,1); glVertex3d(+3,+5,-2);
   glEnd();

   // Cockpit back panel
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_POLYGON);
   normal(-3,5,-2, 3,5,-2, -3,4,-3);
   glTexCoord2f(1,0); glVertex3d(+3,+5,-2);
   glTexCoord2f(0,0); glVertex3d(-3,+5,-2);
   glTexCoord2f(0,1); glVertex3d(-3,+4,-3);
   glTexCoord2f(1,1); glVertex3d(+3,+4,-3);
   glEnd();

   // ---------------------------- Nose panels  ---------------------------
   // Nose top panel
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_POLYGON);
   normal(2,2.5,7, -2,2.5,7, 1,1.5,30);
   glTexCoord2f(0,0); glVertex3d(-2,+2.5,+7);
   glTexCoord2f(0,1); glVertex3d(+2,+2.5,+7);
   glTexCoord2f(1,0); glVertex3d(+1,+1.5,+30);
   glTexCoord2f(1,1); glVertex3d(-1,+1.5,+30);
   glEnd();

   // Nose left bottom panel
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_POLYGON);
   normal(-5,0,-3, -1,-1,30, -2,0,30);
   glTexCoord2f(-1,1); glVertex3d(-5,+0,-3);
   glTexCoord2f(-1,0); glVertex3d(-2,+0,+30);
   glTexCoord2f(1,0); glVertex3d(-1,-1,+30);
   glTexCoord2f(1,1); glVertex3d(-3,-3,-3);
   glEnd();

   // Nose right bottom panel
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_POLYGON);
   normal(5,0,-3, 1,-1,30, 2,0,30);
   glTexCoord2f(-1,1); glVertex3d(+5,+0,-3);
   glTexCoord2f(-1,0); glVertex3d(+2,+0,+30);
   glTexCoord2f(1,0); glVertex3d(+1,-1,+30);
   glTexCoord2f(1,1); glVertex3d(+3,-3,-3);
   glEnd();

   // Nose bottom panel
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_POLYGON);
   normal(3,-3,-3, -3,-3,-3, 1,-1,30);
   glTexCoord2f(-1,1); glVertex3d(-3,-3,-3);
   glTexCoord2f(-1,0); glVertex3d(+3,-3,-3);
   glTexCoord2f(1,0); glVertex3d(+1,-1,+30);
   glTexCoord2f(1,1); glVertex3d(-1,-1,+30);
   glEnd();

   // Nose tip panel
   glBindTexture(GL_TEXTURE_2D,texture[5]);
   glBegin(GL_POLYGON);
   glNormal3d(0,0,1);
   glTexCoord2f(0,0.75); glVertex3d(+1,-1,+30);
   glTexCoord2f(1,0.25); glVertex3d(+2,+0,+30);
   glTexCoord2f(0.677,0.75); glVertex3d(+1,+1.5,+30);
   glTexCoord2f(0.25,0.75); glVertex3d(-1,+1.5,+30);
   glTexCoord2f(0,0.25); glVertex3d(-2,+0,+30);
   glTexCoord2f(0.25,0); glVertex3d(-1,-1,+30);
   glEnd();

   // --------------- Body top and bottom panels -----------------------
   // Body top panel
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_POLYGON);
   glNormal3d(0,1,0);
   glTexCoord2f(1,0.631); glVertex3d(-3,+4,-3);  
   glTexCoord2f(1,0.0901); glVertex3d(+3,+4,-3);
   glTexCoord2f(0.9375,0); glVertex3d(+4,+4,-4);
   glTexCoord2f(0,0.7212); glVertex3d(+4,+4,-19);
   glTexCoord2f(0,0); glVertex3d(-4,+4,-19);
   glTexCoord2f(0.9375,0.7212); glVertex3d(-4,+4,-4);
   glEnd();

   // Body bottom panel
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_POLYGON);
   glNormal3d(0,-1,0);
   glTexCoord2f(1,0.631); glVertex3d(-3,-3,-3);  
   glTexCoord2f(1,0.0901); glVertex3d(+3,-3,-3);
   glTexCoord2f(0.9375,0); glVertex3d(+3,-3,-4);
   glTexCoord2f(0,0.7212); glVertex3d(+3,-3,-19);
   glTexCoord2f(0,0); glVertex3d(-3,-3,-19);
   glTexCoord2f(0.9375,0.7212); glVertex3d(-3,-3,-4);
   glEnd();

   // --------------- Body left panels - behind cockpit to wings -------
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_POLYGON);
   normal(-4,4,-4, -5,0,-4, -3,4,-3);
   glTexCoord2f(0,1); glVertex3d(-3,+4,-3);
   glTexCoord2f(1,1); glVertex3d(-4,+4,-4);
   glTexCoord2f(1,0); glVertex3d(-5,+0,-4);
   glTexCoord2f(0,0); glVertex3d(-5,+0,-3);
   glEnd();

   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_POLYGON);
   normal(-5,0,-4, -4,4,-4, -5,0,-7);
   glTexCoord2f(0,1); glVertex3d(-4,+4,-4);
   glTexCoord2f(0,0); glVertex3d(-5,+0,-4);
   glTexCoord2f(1,0); glVertex3d(-5,+0,-7);
   glTexCoord2f(1,1); glVertex3d(-4,+4,-7);
   glEnd();

   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_POLYGON);
   normal(-5,0,-7, -3,-3,-7, -5,0,-3);
   glTexCoord2f(1,1); glVertex3d(-5,+0,-3);
   glTexCoord2f(0,1); glVertex3d(-5,+0,-7);
   glTexCoord2f(1,0); glVertex3d(-3,-3,-7);
   glTexCoord2f(0,0); glVertex3d(-3,-3,-3);
   glEnd();

   // --------------- Body right panels - behind cockpit to wings -------
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_POLYGON);
   normal(+4,4,-4, +3,4,-3, +5,0,-4);
   glTexCoord2f(1,1); glVertex3d(+3,+4,-3);
   glTexCoord2f(0,1); glVertex3d(+4,+4,-4);
   glTexCoord2f(0,0); glVertex3d(+5,+0,-4);
   glTexCoord2f(1,0); glVertex3d(+5,+0,-3);
   glEnd();

   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_POLYGON);
   normal(+5,0,-4, +5,0,-7, +4,4,-4);
   glTexCoord2f(0,1); glVertex3d(+4,+4,-4);
   glTexCoord2f(1,0); glVertex3d(+5,+0,-4);
   glTexCoord2f(0,0); glVertex3d(+5,+0,-7);
   glTexCoord2f(1,1); glVertex3d(+4,+4,-7);
   glEnd();

   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_POLYGON);
   normal(+5,0,-7, +5,0,-3, +3,-3,-7);
   glTexCoord2f(1,1); glVertex3d(+5,+0,-3);
   glTexCoord2f(0,1); glVertex3d(+5,+0,-7);
   glTexCoord2f(0,0); glVertex3d(+3,-3,-7);
   glTexCoord2f(1,0); glVertex3d(+3,-3,-3);
   glEnd();

   // ---------------- Body inner panels - to hide internals ------------
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_POLYGON);
   glNormal3d(0,0,1);
   glTexCoord2f(0.9,1); glVertex3d(+4,+4,-7);
   glTexCoord2f(1,0.428); glVertex3d(+5,+0,-7);
   glTexCoord2f(0.8,0); glVertex3d(+3,-3,-7);
   glTexCoord2f(0.2,0); glVertex3d(-3,-3,-7);
   glTexCoord2f(0,0.428); glVertex3d(-5,+0,-7);
   glTexCoord2f(0.1,1); glVertex3d(-4,+4,-7);
   glEnd();

   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_POLYGON);
   normal(3,-3,-19, 4,4,-17, 3,-3,-17);
   glTexCoord2f(1,1); glVertex3d(+4,+4,-17);
   glTexCoord2f(1,0); glVertex3d(+3,-3,-17);
   glTexCoord2f(0,0); glVertex3d(+3,-3,-19);
   glTexCoord2f(0,1); glVertex3d(+4,+4,-19);
   glEnd();

   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_POLYGON);
   normal(-3,-3,-19, -3,-3,-17, -4,4,-17);
   glTexCoord2f(0,1); glVertex3d(-4,+4,-17);
   glTexCoord2f(0,0); glVertex3d(-3,-3,-17);
   glTexCoord2f(1,0); glVertex3d(-3,-3,-19);
   glTexCoord2f(1,1); glVertex3d(-4,+4,-19);
   glEnd();

   glBindTexture(GL_TEXTURE_2D,texture[7]);
   glBegin(GL_POLYGON);
   normal(-3,4,0, -3,4,-17, -3,-3,-17);
   glTexCoord2f(0,1); glVertex3d(-3,+4,+0);
   glTexCoord2f(1,1); glVertex3d(-3,+4,-17);
   glTexCoord2f(1,0); glVertex3d(-3,-3,-17);
   glTexCoord2f(0,0); glVertex3d(-3,-3,+0);
   glEnd();

   glBindTexture(GL_TEXTURE_2D,texture[7]);
   glBegin(GL_POLYGON);
   normal(+3,4,0, +3,-3,-17, +3,4,-17);
   glTexCoord2f(1,1); glVertex3d(+3,+4,+0);
   glTexCoord2f(0,1); glVertex3d(+3,+4,-17);
   glTexCoord2f(0,0); glVertex3d(+3,-3,-17);
   glTexCoord2f(1,0); glVertex3d(+3,-3,+0);
   glEnd();

   // ------------------- Body back panels --------------------------------
   glBindTexture(GL_TEXTURE_2D,texture[1]);
   glBegin(GL_POLYGON);
   glNormal3d(0,0,-1);
   glTexCoord2f(0,1); glVertex3d(-4,+4,-19);
   glTexCoord2f(0,0); glVertex3d(-3,-3,-19);
   glTexCoord2f(1,0); glVertex3d(+3,-3,-19);
   glTexCoord2f(1,1); glVertex3d(+4,+4,-19);
   glEnd();

   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_POLYGON);
   glNormal3d(0,0,-1);
   glTexCoord2f(0,0); glVertex3d(-4,+4,-17);
   glTexCoord2f(0,1); glVertex3d(-3,-3,-17);
   glTexCoord2f(1,1); glVertex3d(+3,-3,-17);
   glTexCoord2f(1,0); glVertex3d(+4,+4,-17);
   glEnd();

   // Build wings
   createWings();

   // Disable Textures
   glDisable(GL_TEXTURE_2D);

   //  Undo transofrmations
   glPopMatrix();
}

/*
 *  Draw a Tie-Fighter
 *     
 */
static void tFighter(double x, double y, double z,
                 double dx, double dy, double dz,
                 double rx, double ry, double rz,
                 double th)
{
   //  Save transformation
   glPushMatrix();
   
   //  Offset
   glTranslated(x,y,z);
   glScaled(dx,dy,dz);
   glRotated(th,rx,ry,rz);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);

   // Nose left top panel
   glBindTexture(GL_TEXTURE_2D,texture[9]);
   glBegin(GL_POLYGON);
   glColor3f(0.75,0.75,0.75);
   glNormal3d(1,0,0);
   glTexCoord2f(0.1491,0); glVertex3d(0,0,-5.9560);
   glTexCoord2f(0,0.4931); glVertex3d(0,19.7230,0);
   glTexCoord2f(0.1491,1); glVertex3d(0,40,-5.9560);
   glTexCoord2f(0.7233,1); glVertex3d(0,40,-28.8919);
   glTexCoord2f(0.8807,0.4931); glVertex3d(0,19.730,-35.18);
   glTexCoord2f(0.7233,0); glVertex3d(0,0,-28.8919);
   glEnd();

      // Disable Textures
   glDisable(GL_TEXTURE_2D);

   //  Undo transofrmations
   glPopMatrix();
}

/*
 *  Draw vertex in polar coordinates with normal
 */
static void Vertex(double th,double ph)
{
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   //  For a sphere at the origin, the position
   //  and normal vectors are the same
   glNormal3d(x,y,z);
   glVertex3d(x,y,z);
}

/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius (r)
 */
static void ball(double x,double y,double z,double r)
{
   int th,ph;
   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball
   glColor3f(1,1,1);
   glMaterialfv(GL_FRONT,GL_SHININESS,shinyvec);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
   //  Bands of latitude
   for (ph=-90;ph<90;ph+=inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (th=0;th<=360;th+=2*inc)
      {
         Vertex(th,ph);
         Vertex(th,ph+inc);
      }
      glEnd();
   }
   //  Undo transofrmations
   glPopMatrix();
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);

   //  Undo previous transformations
   glLoadIdentity();
   
   double Ex = -2*dim*Sin(th)*Cos(ph);
   double Ey = +2*dim        *Sin(ph);
   double Ez = +2*dim*Cos(th)*Cos(ph);

   // Call gluLookAt
   gluLookAt(Ex,Ey,Ez, 0,0,0 , 0,Cos(ph),0);

   //  Flat or smooth shading
   glShadeModel(smooth ? GL_SMOOTH : GL_FLAT);

   //  Translate intensity to color vectors
   float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
   float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
   float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};

   //  Light position
   float Position[]  = {distance*Cos(zh),ylight,distance*Sin(zh),1.0};

   //  Draw light position as ball (still no lighting here)
   glColor3f(1,1,1);
   ball(Position[0],Position[1],Position[2] , 0.1);

   //  OpenGL should normalize normal vectors
   glEnable(GL_NORMALIZE);

   //  Enable lighting
   glEnable(GL_LIGHTING);

   //  Location of viewer for specular calculations
   glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);

   //  glColor sets ambient and diffuse color materials
   glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
   glEnable(GL_COLOR_MATERIAL);

   //  Enable light 0
   glEnable(GL_LIGHT0);

   //  Set ambient, diffuse, specular components and position of light 0
   glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
   glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
   glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
   glLightfv(GL_LIGHT0,GL_POSITION,Position);

   // Create XWING
   //xWing(0,0,0, 1,1,1, 0,0,0, 0);

   // Create Tie-Fighter
   tFighter(0,0,0, 1,1,1, 0,0,0, 0);

   //  Done - disable lighting
   glDisable(GL_LIGHTING);
   
   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  Idle function for falling snow
 */
void idle()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360.0);

   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_DOWN)
      dim += 0.1;
   
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_UP && dim>1)
      dim -= 0.1;
   
   //  Smooth color model
   else if (key == GLUT_KEY_F1)
      smooth = 1-smooth;
   
   //  Local Viewer
   else if (key == GLUT_KEY_F2)
      local = 1-local;
   else if (key == GLUT_KEY_F3)
      distance = (distance==1) ? 5 : 1;
   
   //  Toggle ball increment
   else if (key == GLUT_KEY_F8)
      inc = (inc==10)?3:10;
   
   //  Flip sign
   else if (key == GLUT_KEY_F9)
      one = -one;
   
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   
   //  Update projection
   Project(view?fov:0,asp,dim);
   
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   
   //  Reset view angle
   else if (ch == '0')
      th = ph = 0;
   
   //  Toggle light movement
   else if (ch == 'm' || ch == 'M')
      move = 1-move;
   
   //  Move light
   else if (ch == '<')
      zh += 1;
   else if (ch == '>')
      zh -= 1;
   //  Change field of view angle
   else if (ch == '-' && ch>1)
      fov--;
   else if (ch == '+' && ch<179)
      fov++;
   //  Light elevation
   else if (ch=='[')
      ylight -= 0.1;
   else if (ch==']')
      ylight += 0.1;

   //  Translate shininess power to value (-1 => 0)
   shinyvec[0] = shininess<0 ? 0 : pow(2.0,shininess);
   //  Reproject
   Project(view?fov:0,asp,dim);
   //  Animate if requested
   glutIdleFunc(move?idle:NULL);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Set projection
   Project(view?fov:0,asp,dim);
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT
   glutInit(&argc,argv);
   
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(800,800);
   glutCreateWindow("Chris Jordan & Jeremy Granger: Star Wars IV - Death Star Trench Scene");
   
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   
   // Set keyboard functions
   glutSpecialFunc(special);
   glutKeyboardFunc(key);

   // Set idle functions
   glutIdleFunc(idle);

   //  Load textures
   texture[0] = LoadTexBMP("img0.bmp");
   texture[1] = LoadTexBMP("img1.bmp");
   texture[2] = LoadTexBMP("img2.bmp");
   texture[3] = LoadTexBMP("img3.bmp");
   texture[4] = LoadTexBMP("img4.bmp");
   texture[5] = LoadTexBMP("img5.bmp");
   texture[6] = LoadTexBMP("img6.bmp");
   texture[7] = LoadTexBMP("img7.bmp");
   texture[8] = LoadTexBMP("img8.bmp");
   texture[9] = LoadTexBMP("tie-fighter-wing-panel.bmp");

   // Set clock
   ot = clock();

   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
