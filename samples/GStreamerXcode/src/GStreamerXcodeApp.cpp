/*******************************************************************************
 Setup notes
 -----------
 
 1. Add GStreamer framework by dragging to Frameworks
 2. Delete/rename /Library/Frameworks/GStreamer.framework/Headers/assert.h
 3. Edit GStreamer headers to have spaces in literal definitions
 4. Add /Library/Frameworks to Framework Search Paths build setting
 5. Add /Library/Frameworks/GStreamer.framework/Headers to Header Search Paths
    build setting
 6. Add _2RealGStreamerWrapper/include to Header Search Paths build setting
 
 (modified 2Real.h to undef BIG_ENDIAN and LITTLE_ENDIAN on all but MSW)
 
*******************************************************************************/

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"

#include "_2RealGstreamerWrapper.h"

class GStreamerXcodeApp : public ci::app::AppNative {
public:
    GStreamerXcodeApp();
	void setup();
	void mouseDown( ci::app::MouseEvent event );
	void update();
	void draw();

private:
    _2RealGStreamerWrapper::GStreamerWrapperRef     mPlayer;
    ci::gl::TextureRef                              mVideoTex;
};

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace _2RealGStreamerWrapper;

GStreamerXcodeApp::GStreamerXcodeApp() :
AppNative(),
mPlayer( nullptr ),
mVideoTex( nullptr )
{
}

void
GStreamerXcodeApp::setup()
{
    mPlayer = GStreamerWrapper::create( "http://video.webmfiles.org/big-buck-bunny_trailer.webm" );
    mPlayer->play();
}

void
GStreamerXcodeApp::mouseDown( MouseEvent event )
{
}

void
GStreamerXcodeApp::update()
{
}

void
GStreamerXcodeApp::draw()
{
    gl::clear();

    if ( mPlayer && mPlayer->isNewVideoFrame() ) {
        unsigned char* pImg = mPlayer->getVideo();
        if(pImg != nullptr)
        {
            mVideoTex = gl::Texture::create( ci::Surface( pImg, mPlayer->getWidth(), mPlayer->getHeight(), mPlayer->getWidth() * 3, ci::SurfaceChannelOrder::RGB ) );
        }
    }

    if ( mVideoTex ) gl::draw( mVideoTex );
}

CINDER_APP_NATIVE( GStreamerXcodeApp, RendererGl )
