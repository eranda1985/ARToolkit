/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _ 
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/                              
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#include "TutorialApplication.h"
#include "OgreHardwarePixelBuffer.h"

//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
}
//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
    // create your scene here :)

	// Set the scene's ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));

	// Create an Entity
    Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
 
    // Create a SceneNode and attach the Entity to it
    headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("HeadNode");
    headNode->attachObject(ogreHead);
	headNode->setPosition(Ogre::Vector3(0,0,-120));
	

	// Create a Light and set its position
    Ogre::Light* light = mSceneMgr->createLight("MainLight");
    light->setPosition(20.0f, 80.0f, 50.0f);

	//------------------------------------------------------------------------------------------------------------
	// Create RGB texture with 0 mipmap
		Ogre::TexturePtr tex = Ogre::TextureManager::getSingleton().createManual(
			"MyManualTexture", // Name of texture
			"Popular", // Name of resource group in which the texture should be created
			Ogre::TEX_TYPE_2D, // Texture type
			640, // Width
			480, // Height
			//1, // Depth (Must be 1 for two dimensional textures)
			0, // Number of mipmaps
			Ogre::PF_X8R8G8B8, // Pixel format
			Ogre::TU_DYNAMIC_WRITE_ONLY_DISCARDABLE
			);
		buffer = tex->getBuffer();

		// Lock the pixel buffer and get a pixel box
		buffer->lock(Ogre::HardwareBuffer::HBL_NORMAL); // for best performance use HBL_DISCARD!
		const Ogre::PixelBox& pixelBox = buffer->getCurrentLock();
 
		pDest = static_cast<UINT8*>(pixelBox.data);
 
		// Fill in some pixel data. This will give a semi-transparent blue,
		// but this is of course dependent on the chosen pixel format.
		/*for (size_t j = 0; j < 640; j++)
			for(size_t i = 0; i < 480; i++)
			{
				*pDest++ = 0; // B
				*pDest++ =   255; // G
				*pDest++ =   0; // R
				*pDest++ = 0; // A


			}*/

		for(int i = 0; i < 1228800; i++)
			{
				*pDest = frameBuffer[i];
				pDest++;

			}

		flag1 = true;
 
		// Unlock the pixel buffer
		buffer->unlock();

		// Create a material using the texture
		Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(
    "BackgroundMat", // name
	"Popular");
 
		material->getTechnique(0)->getPass(0)->createTextureUnitState("MyManualTexture");
		material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
		material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
		material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
		//material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);



		// Create background rectangle covering the whole screen
		Ogre::Rectangle2D* rect = new Ogre::Rectangle2D(true);
		rect->setCorners(-1.0, 1.0, 1.0, -1.0);
		
		rect->setMaterial("BackgroundMat");

		// Use infinite AAB to always stay visible
		Ogre::AxisAlignedBox aabInf;
		aabInf.setInfinite();
		rect->setBoundingBox(aabInf);
 
		// Render the background before everything else
		rect->setRenderQueueGroup(Ogre::RENDER_QUEUE_BACKGROUND);
 
		
 
		// Attach background to the scene
		Ogre::SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Background");
		node->attachObject(rect);
		//--------------------------------------------------------------------------------------------------------------

	
}



#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif


//#ifdef __cplusplus
//extern "C" {
//#endif
//
//#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
//    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
//
//#else
//    int main(int argc, char *argv[])
//#endif
//    {
//        // Create application object
//        TutorialApplication app;
//
//        try {
//            app.go();
//        } catch( Ogre::Exception& e ) {
//#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
//            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
//#else
//            std::cerr << "An exception has occured: " <<
//                e.getFullDescription().c_str() << std::endl;
//#endif
//        }
//
//        return 0;
//    }
//
//#ifdef __cplusplus
//}
//#endif  
