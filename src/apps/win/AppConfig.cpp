/*
    cam2web - streaming camera to web

    Copyright (C) 2017, cvsandbox, cvsandbox@gmail.com

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include <list>

#include "AppConfig.hpp"

using namespace std;

// Macro to make sure a value is in certain range
#define XINRANGE(a, min, max) (((a)<(max))?(((a)>(min))?(a):(min)):(max))

#define PROP_JPEG_QUALITY   "jpegQuality"
#define PROP_MJPEG_RATE     "mjpegRate"
#define PROP_HTTP_PORT      "httpPort"
#define PROP_AUTH_DOMAIN    "authDomain"
#define PROP_CUSTOM_WEB     "customWeb"
#define PROP_CAMERA_MONIKER "cameraMoniker"
#define PROP_CAMERA_WIDTH   "cameraWidth"
#define PROP_CAMERA_HEIGHT  "cameraHeight"
#define PROP_CAMERA_BPP     "cameraBpp"
#define PROP_CAMERA_FPS     "cameraFps"

// List of supported properties
const static list<string> SupportedProperties =
{
    PROP_JPEG_QUALITY, PROP_MJPEG_RATE, PROP_HTTP_PORT, PROP_AUTH_DOMAIN, PROP_CUSTOM_WEB,
    PROP_CAMERA_MONIKER, PROP_CAMERA_WIDTH, PROP_CAMERA_HEIGHT, PROP_CAMERA_BPP, PROP_CAMERA_FPS
};

AppConfig::AppConfig( ) :
    jpegQuality( 85 ),
    mjpegFrameRate( 30 ),
    httpPort( 8000 ),
    authDomain( "cam2web" ),
    customWebContent( ),
    cameraMoniker( ),
    cameraWidth( 0 ),
    cameraHeight( 0 ),
    cameraBpp( 0 ),
    cameraFps( 0 )
{

}

// Get/Set JPEG quality
uint16_t AppConfig::JpegQuality( ) const
{
    return jpegQuality;
}
void AppConfig::SetJpegQuality( uint16_t quality )
{
    jpegQuality = XINRANGE( quality, 1, 100 );
}

// Get/Set MJPEG frame rate
uint16_t AppConfig::MjpegFrameRate( ) const
{
    return mjpegFrameRate;
}
void AppConfig::SetMjpegFrameRate( uint16_t frameRate )
{
    mjpegFrameRate = XINRANGE( frameRate, 1, 30 );
}

// Get Set HTTP port to listen
uint16_t AppConfig::HttpPort( ) const
{
    return httpPort;
}
void AppConfig::SetHttpPort( uint16_t port )
{
    httpPort = XINRANGE( port, 1, 65535 );
}

// Get/Set HTTP digest auth domain
string AppConfig::AuthDomain( ) const
{
    return authDomain;
}
void AppConfig::SetAuthDomain( const string& domain )
{
    authDomain = domain;
}

// Get/Set path to the folder with custom web content
string AppConfig::CustomWebContent( ) const
{
    return customWebContent;
}
void AppConfig::SetCustomWebContent( const string& path )
{
    customWebContent = path;
}

// Get/Set camera moniker string
string AppConfig::CameraMoniker( ) const
{
    return cameraMoniker;
}
void AppConfig::SetCameraMoniker( const string& moniker )
{
    cameraMoniker = moniker;
}

// Get/Set last used video resolution
void AppConfig::GetLastVideoResolution( uint16_t* width, uint16_t* height, uint16_t* bpp, uint16_t* fps )
{
    if ( width  != nullptr ) *width  = cameraWidth;
    if ( height != nullptr ) *height = cameraHeight;
    if ( bpp    != nullptr ) *bpp    = cameraBpp;
    if ( fps    != nullptr ) *fps    = cameraFps;
}
void AppConfig::SetLastVideoResolution( uint16_t width, uint16_t height, uint16_t bpp, uint16_t fps )
{
    cameraWidth  = width;
    cameraHeight = height;
    cameraBpp    = bpp;
    cameraFps    = fps;
}

// Set property of the object
XError AppConfig::SetProperty( const string& propertyName, const string& value )
{
    XError  ret = XError::Success;
    int32_t intValue;
    int     scanned = sscanf( value.c_str( ), "%d", &intValue );

    if ( propertyName == PROP_JPEG_QUALITY )
    {
        if ( scanned != 1 )
        {
            ret = XError::InvalidPropertyValue;
        }
        else
        {
            jpegQuality = static_cast<uint16_t>( intValue );
        }
    }
    else if ( propertyName == PROP_MJPEG_RATE )
    {
        if ( scanned != 1 )
        {
            ret = XError::InvalidPropertyValue;
        }
        else
        {
            mjpegFrameRate = static_cast<uint16_t>( intValue );
        }
    }
    else if ( propertyName == PROP_HTTP_PORT )
    {
        if ( scanned != 1 )
        {
            ret = XError::InvalidPropertyValue;
        }
        else
        {
            httpPort = static_cast<uint16_t>( intValue );
        }
    }
    else if ( propertyName == PROP_AUTH_DOMAIN )
    {
        authDomain = value;
    }
    else if ( propertyName == PROP_CUSTOM_WEB )
    {
        customWebContent = value;
    }
    else if ( propertyName == PROP_CAMERA_MONIKER )
    {
        cameraMoniker = value;
    }
    else if ( propertyName == PROP_CAMERA_WIDTH )
    {
        if ( scanned != 1 )
        {
            ret = XError::InvalidPropertyValue;
        }
        else
        {
            cameraWidth = static_cast<uint16_t>( intValue );
        }
    }
    else if ( propertyName == PROP_CAMERA_HEIGHT )
    {
        if ( scanned != 1 )
        {
            ret = XError::InvalidPropertyValue;
        }
        else
        {
            cameraHeight = static_cast<uint16_t>( intValue );
        }
    }
    else if ( propertyName == PROP_CAMERA_BPP )
    {
        if ( scanned != 1 )
        {
            ret = XError::InvalidPropertyValue;
        }
        else
        {
            cameraBpp = static_cast<uint16_t>( intValue );
        }
    }
    else if ( propertyName == PROP_CAMERA_FPS )
    {
        if ( scanned != 1 )
        {
            ret = XError::InvalidPropertyValue;
        }
        else
        {
            cameraFps = static_cast<uint16_t>( intValue );
        }
    }
    else
    {
        ret = XError::UnknownProperty;
    }

    return ret;
}

// Get property of the object
XError AppConfig::GetProperty( const string& propertyName, string& value ) const
{
    XError  ret         = XError::Success;
    int32_t intValue    = 0;
    bool    numericProp = false;

    if ( propertyName == PROP_JPEG_QUALITY )
    {
        intValue    = jpegQuality;
        numericProp = true;
    }
    else if ( propertyName == PROP_MJPEG_RATE )
    {
        intValue    = mjpegFrameRate;
        numericProp = true;
    }
    else if ( propertyName == PROP_HTTP_PORT )
    {
        intValue    = httpPort;
        numericProp = true;
    }
    else if ( propertyName == PROP_AUTH_DOMAIN )
    {
        value = authDomain;
    }
    else if ( propertyName == PROP_CUSTOM_WEB )
    {
        value = customWebContent;
    }
    else if ( propertyName == PROP_CAMERA_MONIKER )
    {
        value = cameraMoniker;
    }
    else if ( propertyName == PROP_CAMERA_WIDTH )
    {
        intValue    = cameraWidth;
        numericProp = true;
    }
    else if ( propertyName == PROP_CAMERA_HEIGHT )
    {
        intValue    = cameraHeight;
        numericProp = true;
    }
    else if ( propertyName == PROP_CAMERA_BPP )
    {
        intValue    = cameraBpp;
        numericProp = true;
    }
    else if ( propertyName == PROP_CAMERA_FPS )
    {
        intValue    = cameraFps;
        numericProp = true;
    }
    else
    {
        ret = XError::UnknownProperty;
    }

    if ( ( ret ) && ( numericProp ) )
    {
        char buffer[32];

        sprintf( buffer, "%d", intValue );
        value = buffer;
    }

    return ret;
}

// Get all properties of the object
map<string, string> AppConfig::GetAllProperties( ) const
{
    map<string, string> properties;
    string              value;

    for ( auto property : SupportedProperties )
    {
        if ( GetProperty( property, value ) )
        {
            properties.insert( pair<string, string>( property, value ) );
        }
    }

    return properties;
}
