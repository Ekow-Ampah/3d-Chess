#include "GLViewNewModule.h"
#include "WorldList.h" //This is where we place all of our WOs
#include "ManagerOpenGLState.h" //We can change OpenGL State attributes with this
#include "Axes.h" //We can set Axes to on/off with this
#include "PhysicsEngineODE.h"
#include "irrKlang.h"
//Different WO used by this module
#include "WO.h"
#include "WOStatic.h"
#include "WOStaticPlane.h"
#include "WOStaticTrimesh.h"
#include "WOTrimesh.h"
#include "WOHumanCyborg.h"
#include "WOHumanCal3DPaladin.h"
#include "WOWayPointSpherical.h"
#include "WOLight.h"
#include "WOSkyBox.h"
#include "WOCar1970sBeater.h"
#include "Camera.h"
#include "CameraStandard.h"
#include "CameraChaseActorSmooth.h"
#include "CameraChaseActorAbsNormal.h"
#include "CameraChaseActorRelNormal.h"
#include "Model.h"
#include "ModelDataShared.h"
#include "ModelMesh.h"
#include "ModelMeshDataShared.h"
#include "ModelMeshSkin.h"
#include "WONVStaticPlane.h"
#include "WONVPhysX.h"
#include "WONVDynSphere.h"
#include "WOImGui.h" //GUI Demos also need to #include "AftrImGuiIncludes.h"
#include "AftrImGuiIncludes.h"
#include "AftrGLRendererBase.h"

using namespace Aftr;
using namespace irrklang;



GLViewNewModule* GLViewNewModule::New( const std::vector< std::string >& args )
{
   GLViewNewModule* glv = new GLViewNewModule( args );
   glv->init( Aftr::GRAVITY, Vector( 0, 0, -1.0f ), "aftr.conf", PHYSICS_ENGINE_TYPE::petODE );
   glv->onCreate();
   return glv;
}


GLViewNewModule::GLViewNewModule( const std::vector< std::string >& args ) : GLView( args )
{
    //ISoundEngine* engine = createIrrKlangDevice();

   //Initialize any member variables that need to be used inside of LoadMap() here.
   //Note: At this point, the Managers are not yet initialized. The Engine initialization
   //occurs immediately after this method returns (see GLViewNewModule::New() for
   //reference). Then the engine invoke's GLView::loadMap() for this module.
   //After loadMap() returns, GLView::onCreate is finally invoked.

   //The order of execution of a module startup:
   //GLView::New() is invoked:
   //    calls GLView::init()
   //       calls GLView::loadMap() (as well as initializing the engine's Managers)
   //    calls GLView::onCreate()

   //GLViewNewModule::onCreate() is invoked after this module's LoadMap() is completed.
}


void GLViewNewModule::onCreate()
{
   //GLViewNewModule::onCreate() is invoked after this module's LoadMap() is completed.
   //At this point, all the managers are initialized. That is, the engine is fully initialized.

   if( this->pe != NULL )
   {
      //optionally, change gravity direction and magnitude here
      //The user could load these values from the module's aftr.conf
      this->pe->setGravityNormalizedVector( Vector( 0,0,-1.0f ) );
      this->pe->setGravityScalar( Aftr::GRAVITY );
   }
   this->setActorChaseType( STANDARDEZNAV ); //Default is STANDARDEZNAV mode
   //this->setNumPhysicsStepsPerRender( 0 ); //pause physics engine on start up; will remain paused till set to 1
}


GLViewNewModule::~GLViewNewModule()
{
   //Implicitly calls GLView::~GLView()
}


void GLViewNewModule::updateWorld()
{
   GLView::updateWorld(); //Just call the parent's update world first.
                          //If you want to add additional functionality, do it after
                          //this call.
  
}


void GLViewNewModule::onResizeWindow( GLsizei width, GLsizei height )
{
   GLView::onResizeWindow( width, height ); //call parent's resize method.
}


void GLViewNewModule::onMouseDown( const SDL_MouseButtonEvent& e )
{
   GLView::onMouseDown( e );
}


void GLViewNewModule::onMouseUp( const SDL_MouseButtonEvent& e )
{
   GLView::onMouseUp( e );
}


void GLViewNewModule::onMouseMove( const SDL_MouseMotionEvent& e )
{
   GLView::onMouseMove( e );
}


void GLViewNewModule::onKeyDown( const SDL_KeyboardEvent& key )
{
   GLView::onKeyDown( key );
   if( key.keysym.sym == SDLK_0 )
      this->setNumPhysicsStepsPerRender( 1 );

   if( key.keysym.sym == SDLK_1 )
   {
       //irrklang::ISoundEngine* engine = createIrrKlangDevice();
      // irrklang::ISound* s = engine->play2D((ManagerEnvironmentConfiguration::getSMM() + "C:/repos/aburn/usr/shared/mm/sounds/sound2.wav").c_str());
     

      
   }
}


void GLViewNewModule::onKeyUp( const SDL_KeyboardEvent& key )
{
   GLView::onKeyUp( key );
}


void Aftr::GLViewNewModule::loadMap()
{
    //irrklang::ISoundEngine* engine = createIrrKlangDevice();
    //engine->play2D((ManagerEnvironmentConfiguration::getSMM() + "C:/repos/aburn/usr/shared/mm/sounds/sound2.wav").c_str());
   this->worldLst = new WorldList(); //WorldList is a 'smart' vector that is used to store WO*'s
   this->actorLst = new WorldList();
   this->netLst = new WorldList();

   
   ManagerOpenGLState::GL_CLIPPING_PLANE = 1000.0;
   ManagerOpenGLState::GL_NEAR_PLANE = 0.1f;
   ManagerOpenGLState::enableFrustumCulling = false;
   Axes::isVisible = true;
   this->glRenderer->isUsingShadowMapping( false ); //set to TRUE to enable shadow mapping, must be using GL 3.2+

   this->cam->setPosition( 15,15,10 );

   std::string shinyRedPlasticCube( ManagerEnvironmentConfiguration::getSMM() + "/models/cube4x4x4redShinyPlastic_pp.wrl" );
   std::string wheeledCar( ManagerEnvironmentConfiguration::getSMM() + "/models/rcx_treads.wrl" );
   std::string grass( ManagerEnvironmentConfiguration::getSMM() + "/models/grassFloor400x400_pp.wrl" );
   std::string human( ManagerEnvironmentConfiguration::getSMM() + "/models/human_chest.wrl" );
   
   //SkyBox Textures readily available
   std::vector< std::string > skyBoxImageNames; //vector to store texture paths
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_water+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_dust+6.jpg" );
   skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_mountains+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_winter+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/early_morning+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_afternoon+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_cloudy+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_cloudy3+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_day+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_day2+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_deepsun+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_evening+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_morning+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_morning2+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_noon+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_warp+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_Hubble_Nebula+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_gray_matter+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_easter+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_hot_nebula+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_ice_field+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_lemon_lime+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_milk_chocolate+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_solar_bloom+6.jpg" );
   //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_thick_rb+6.jpg" );

   {
      //Create a light
      float ga = 0.1f; //Global Ambient Light level for this module
      ManagerLight::setGlobalAmbientLight( aftrColor4f( ga, ga, ga, 1.0f ) );
      WOLight* light = WOLight::New();
      light->isDirectionalLight( true );
      light->setPosition( Vector( 0, 0, 100 ) );
      //Set the light's display matrix such that it casts light in a direction parallel to the -z axis (ie, downwards as though it was "high noon")
      //for shadow mapping to work, this->glRenderer->isUsingShadowMapping( true ), must be invoked.
      light->getModel()->setDisplayMatrix( Mat4::rotateIdentityMat( { 0, 1, 0 }, 90.0f * Aftr::DEGtoRAD ) );
      light->setLabel( "Light" );
      worldLst->push_back( light );
   }

   {
      //Create the SkyBox
      WO* wo = WOSkyBox::New( skyBoxImageNames.at( 0 ), this->getCameraPtrPtr() );
      wo->setPosition( Vector( 0, 0, 0 ) );
      wo->setLabel( "Sky Box" );
      wo->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
      worldLst->push_back( wo );
   }

  
   { 
       WO* wo = WO::New("../../../shared/mm/Assimp/model.dae");
       

  
  // wo->rotateAboutRelX(150);
   wo->setPosition(Vector(0, 0, 0));
   //Material* material = MaterialManager::getInstance()->createMaterial("MyMaterial");
   wo->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
   worldLst->push_back(wo);
   }
   
       const int boardSize = 8;
       const float squareSize = 8.0f; 

       WO* pawnBoard[boardSize][boardSize]; 
       int track[boardSize][boardSize];
       for (int i = 0; i < boardSize; i++) {
           for (int j = 0; j < boardSize; j++) {
               track[i][j] = 0;
           }
       }
       for (int row = 0; row < boardSize; row++) {
           for (int col = 0; col < boardSize; col++) {
               float xPos = col * squareSize;
               float yPos = row * squareSize;

               WO* square = WO::New("../../../shared/mm/Assimp/board.3ds");
               
               square->rotateAboutRelX(300);
               square->setPosition(Vector(xPos, yPos, 0));
               square->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
               worldLst->push_back(square);

               
               if ((row + col) % 2 == 0) {
                   if (row < 3) {
                       WO* pawn = WO::New("../../../shared/mm/Assimp/Pawn.3ds");
                       

                       pawn->rotateAboutRelX(300);
                       pawn->setPosition(Vector(xPos, yPos, 4)); 
                       pawn->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
                       worldLst->push_back(pawn);

                       
                       pawnBoard[row][col] = pawn;
                       track[row][col] = 1;
                   }
                   else if (row > 4) {
                       WO* pawn = WO::New("../../../shared/mm/Assimp/Pawn.3ds");
                       
                       pawn->rotateAboutRelX(300);
                       pawn->setPosition(Vector(xPos, yPos, 4)); 
                       pawn->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
                       worldLst->push_back(pawn);

                       
                       pawnBoard[row][col] = pawn;
                       track[row][col] = 2;
                   }
               }
           }
       }
       bool IsValidMove(int array[][8], int fromcol, int fromrow, int tocol, int torow, bool player);

   
       WOImGui* gui = WOImGui::New(nullptr);
       gui->setLabel("3D Chess");
       bool startNewGame = false;
       bool p1 = true;
       gui->subscribe_drawImGuiWidget([this, p1, gui, track]() mutable {
           
          
       
         
           
           if (ImGui::Begin("3D Chess"))
           {
               if (ImGui::Button("Start New Game")) { //reset game
                   int initialTrack[8][8] = {
                {1, 0, 1, 0, 1, 0, 1, 0},
                {0, 1, 0, 1, 0, 1, 0, 1},
                {1, 0, 1, 0, 1, 0, 1, 0},
                {0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0},
                {0, 2, 0, 2, 0, 2, 0, 2},
                {2, 0, 2, 0, 2, 0, 2, 0},
                {0, 2, 0, 2, 0, 2, 0, 2}
                   };
                   // Assign to inital state
                   for (int i = 0; i < 8; i++) {
                       for (int j = 0; j < 8; j++) {
                           track[i][j] = initialTrack[i][j];
                       }
                   }
                   p1 = true; // reset back to player one move
               }
                   ImGui::Text(" 1   2   3   4   5   6   7   8");
                   for (int i = 0; i < 8; i++)
                   {
                       for (int j = 0; j < 8; j++)
                       {
                           if (track[i][j] == 1)
                           {
                               ImGui::Text("[0]");
                           }
                           else if (track[i][j] == 2)
                           {
                               ImGui::Text("[X]");
                           }
                           else
                           {
                               ImGui::Text("[-]");
                           }
                           ImGui::SameLine();
                       }
                       ImGui::Text(" %d ", i + 1);
                       ImGui::NewLine();
                   }
               
               static int fromColumn = 0, fromRow = 0, toColumn = 0, toRow = 0;
               if (p1) {
                   ImGui::Text("Player 1 (X) what piece would you like to move: ");
               }
               else {
                   ImGui::Text("Player 2 (0) what piece would you like to move: ");
               }
               ImGui::InputInt("From Column", &fromColumn, 1);
               ImGui::InputInt("From Row", &fromRow, 1);
               ImGui::InputInt("To Column", &toColumn, 1);
               ImGui::InputInt("To Row", &toRow, 1);
               if (ImGui::Button("Submit")) {
                   if (IsValidMove(track, fromColumn-1, fromRow-1, toColumn-1, toRow-1, p1)) {
                       if (p1) {
                           track[toRow -1 ][toColumn -1 ] = 2;
                           track[fromRow - 1][fromColumn - 1] = 0;
                           int check = abs(fromColumn - toColumn) ;
                           if (check == 2) {
                               int tmp = track[((fromRow + toRow - 2) / 2)][((fromColumn + toColumn - 2) / 2)];
                               if (tmp != 0) {
                                   track[(fromRow + toRow - 2) / 2][(fromColumn + toColumn - 2) / 2] = 0;
                               }
                           }
                           fromColumn = 0, fromRow = 0, toColumn = 0, toRow = 0;
                           p1 = false;
                           //ImGui::Render();
                           //ImGui::Text("Worked");
                       }
                       else {
                           track[toRow - 1][toColumn - 1] = 1;
                           track[fromRow - 1][fromColumn - 1] = 0;
                           int check = abs(fromColumn - toColumn);
                           if (check == 2) {
                               int tmp = track[(fromRow + toRow - 2) / 2][(fromColumn + toColumn - 2) / 2];

                               if (tmp != 0) {
                                   track[(fromRow + toRow - 2) / 2][(fromColumn + toColumn - 2) / 2] = 0;
                               }
                           }
                           fromColumn = 0, fromRow = 0, toColumn = 0, toRow = 0;
                           p1 = true;

                           //ImGui::Render();
                           //ImGui::Text("Worked");
                       }
                   }
                   else {
                       ImGui::Text("INVALID MOVE!!!!");
                   }
               }
               int player1_piece = 0;
               int player2_piece = 0;
               for (int i = 0; i < 8; i++) {
                   
                   for (int j = 0; j < 8; j++) {
                       if(track[i][j] == 2){
                           player1_piece++;
                       }
                       else if (track[i][j] == 1) {
                           player2_piece++;
                       }
                       else {
                       //do nothing
                       }
               }
              
           }
               if (player1_piece == 0) {
                   ImGui::Text("Player 2 Wins!!!!");
               }else if (player2_piece == 0) {
                   ImGui::Text("Player 1 Wins!!!!");
               }
               else {

               }


               ImGui::End();
           }
           });



this->worldLst->push_back(gui);

createNewModuleWayPoints();

   
}
bool IsValidMove(int array[][8], int fromcol, int fromrow, int tocol, int torow, bool player){
        int colDiff = abs(fromcol - tocol); //abs so can focus on only postive
        int rowDiff = (fromrow - torow);

    if (fromcol < 0 || fromrow < 0 || tocol < 0 || torow < 0 ||
        fromcol > 7 || fromrow > 7 || tocol > 7 || torow > 7) {  // cant be less or greater than 7
        
        return false;
    }
    if (array[torow][tocol] != 0) { // must be empty
        
        return false;
    }
    if (colDiff == 0 || rowDiff == 0) { // cant move to same spot
        return false;
    }
    
     if (player && array[fromrow][fromcol] == 2) {
         if (rowDiff == 1) {
             if (colDiff == 1) {
                 return true;
             }
         }
         else if (rowDiff == 2) {
             if (colDiff == 2) {
                 int tmp = array[(fromrow + torow)/2][(fromcol + tocol)/2];
                 if (tmp != 0 && tmp !=2) {
                     return true;
                 }
             }
       }
    }
     if (!player && array[fromrow][fromcol] == 1) {
         if (rowDiff == -1) {
             if (colDiff == 1) {
                 return true;
             }
         }
         else if (rowDiff == -2) {
             if (colDiff == 2) {
                 int tmp = array[(fromrow + torow) / 2][(fromcol + tocol) / 2];
                 if (tmp != 0 && tmp != 1) {
                     return true;
                 }
             }
         }
     }
     return false;

    
}


void GLViewNewModule::createNewModuleWayPoints()
{
   // Create a waypoint with a radius of 3, a frequency of 5 seconds, activated by GLView's camera, and is visible.
   WayPointParametersBase params(this);
   params.frequency = 5000;
   params.useCamera = true;
   params.visible = true;
   WOWayPointSpherical* wayPt = WOWayPointSpherical::New( params, 3 );
   wayPt->setPosition( Vector( 50, 0, 3 ) );
   worldLst->push_back( wayPt );
}
