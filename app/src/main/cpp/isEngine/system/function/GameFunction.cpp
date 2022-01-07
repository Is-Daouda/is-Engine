/*
  is::Engine (Infinity Solutions Engine)
  Copyright (C) 2018-2022 Is Daouda <isdaouda.n@gmail.com>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include "GameFunction.h"

namespace is
{
float const MAX_CLOCK_TIME = 0.018f;
float const VALUE_CONVERSION = 65.f;
float const SECOND = 59.f;
float const VALUE_TIME = 1.538f;

std::string w_chart_tToStr(wchar_t const *val)
{
    std::wstring ws(val);
    return (std::string(ws.begin(), ws.end()));
}

std::wstring strToWStr(const std::string &str)
{
    std::wstring wsTemp(str.begin(), str.end());
    return wsTemp;
}

int getMSecond(float const &DELTA_TIME)
{
    return static_cast<int>(DELTA_TIME * (VALUE_TIME * VALUE_CONVERSION));
}

std::tm makeTime(int year, int month, int day)
{
    std::tm tm = {0};
    tm.tm_year = year - 1900; // years count from 1900
    tm.tm_mon = month - 1;    // months count from January=0
    tm.tm_mday = day;         // days count from 1
    return tm;
}

void showLog(const std::string& str, bool stopApplication)
{
    #if defined(IS_ENGINE_USE_SHOWLOG)
    #if !defined(__ANDROID__)
    std::cout << str.c_str() << "\n";
    #else
    __android_log_print(ANDROID_LOG_DEBUG, "LOG_INFO", "%s\n", str.c_str());
    #endif
    #endif // defined
    if (stopApplication) is::closeApplication();
}

bool isIn(unsigned short valNumber, int const var, int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8, int x9)
{
    if (var == x1) return true;
    else if (var == x2) return true;
    else if (var == x3) return (valNumber > 2);
    else if (var == x4) return (valNumber > 3);
    else if (var == x5) return (valNumber > 4);
    else if (var == x6) return (valNumber > 5);
    else if (var == x7) return (valNumber > 6);
    else if (var == x8) return (valNumber > 7);
    else if (var == x9) return (valNumber > 8);
    return false;
}

bool isBetween(float a, float b, float c)
{
    if (b <= c) return (b <= a && a <= c);
    else return (c <= a && a <= b);
}

int sign(float x)
{
    if (x > 0.f)      return 1;
    else if (x < 0.f) return -1;
    else return 0;
}

float pointDirection(float x1, float y1, float x2, float y2)
{
    return atan((y1 - y2) / (x1 - x2));
}

float radToDeg(float x)
{
    return static_cast<float>((x * 180.f) / 3.14159235f);
}

float degToRad(float x)
{
    return static_cast<float>((x * 3.14159235f) / 180.f);
}

float lengthDirX(float dir, float angle)
{
    return dir * std::cos(degToRad(angle));
}

float lengthDirY(float dir, float angle)
{
    return dir * std::sin(degToRad(angle));
}

bool collisionTest(Rectangle const &a, Rectangle const &b)
{
    if (a.m_bottom <= b.m_top)    return false;
    if (a.m_top    >= b.m_bottom) return false;
    if (a.m_right  <= b.m_left)   return false;
    if (a.m_left   >= b.m_right)  return false;
    return true;
}

bool collisionTest(Circle const &a, Circle const &b)
{
    auto distanceSquared = [](int x1, int y1, int x2, int y2)
    {
        int deltaX = x2 - x1;
        int deltaY = y2 - y1;
        return deltaX * deltaX + deltaY * deltaY;
    };

    // Calculate total radius squared
    int totalRadiusSquared = a.m_raduis + b.m_raduis;
    totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

    // If the distance between the centers of the circles is less than the sum of their radii
    if (distanceSquared(a.m_x, a.m_y, b.m_x, b.m_y) < totalRadiusSquared) return true; // The circles have collided
    return false; // If not
}

bool collisionTest(Circle const &circle, Rectangle const &rec)
{
    // temporary variables to set edges for testing
    float testX = circle.m_x;
    float testY = circle.m_y;

    // which edge is closest?
    if (circle.m_x < rec.m_left) testX = rec.m_left;   // test left edge
    else if (circle.m_x > rec.m_right)   testX = rec.m_right;  // right edge
    if (circle.m_y < rec.m_top)  testY = rec.m_top;    // top edge
    else if (circle.m_y > rec.m_bottom)  testY = rec.m_bottom; // bottom edge

    // get distance from closest edges
    float distX = circle.m_x - testX;
    float distY = circle.m_y - testY;
    float distance = sqrt((distX * distX) + (distY * distY));

    // if the distance is less than the radius, collision!
    if (distance <= circle.m_raduis) return true;
    return false;
}

bool collisionTest(Rectangle const &rec, Circle const &circle)
{
    return collisionTest(circle, rec);
}

void setFrame(sf::Sprite &sprite, float frame, int subFrame, int frameWidth, int frameHeight, int recWidth, int recHeight)
{
    /* Description of the image decoupage algorithm
     * be << frame >> number of the image to get (to have it start counting images from 0 to X)
     * either << subFrame >> number of images on one line
     * be << frameLineIndex >> number of the line corresponding to the image
     * (frame / subFrame) returns the number of times there is << frame >> in << subFrame >> to determine the number of the line of the image
     * 32 * (frame - (subFrame * frameLineIndex)) returns the position (number) of the image on the X axis can return the value 0 (1st image on the line)
     * when the value of << frame >> exceeds the number of image on the X axis (the value of << subFrame >>) then we are on a new line
     * (32 * frameLineIndex) gives the position of the image on the Y axis its value varies according to the << frame >>
     * example: 32 * frameLineIndex = 1 when frame > subFrame; 32 * frameLineIndex = 2 when frame > subFrame * 2; ...
     */
    int frameLineIndex = (frame / subFrame);
    setSFMLObjTexRec(sprite, frameWidth * (static_cast<int>(frame) - (subFrame * frameLineIndex)), frameHeight * frameLineIndex, recWidth, recHeight);
}

void setFrame(sf::Sprite &sprite, float frame, int subFrame, int frameSize)
{
    setFrame(sprite, frame, subFrame, frameSize, frameSize, frameSize, frameSize);
}

/*
void createRenderTexture(sf::RenderTexture &renderTexture, unsigned int width, unsigned int height)
{
    renderTexture.create(width, height);
}*/

void createRectangle(sf::RectangleShape &rec, sf::Vector2f recSize, sf::Color color, float x, float y, bool center)
{
    rec.setSize(recSize);
    if (center) is::centerSFMLObj(rec);
    setSFMLObjFillColor(rec, color);
    is::setSFMLObjX_Y(rec, x, y);
}

void textStyleConfig(sf::Text &txt, bool underLined, bool boldText, bool italicText)
{
    if (underLined && boldText && italicText) txt.setStyle(sf::Text::Underlined | sf::Text::Bold | sf::Text::Italic);
    else if (underLined && boldText)          txt.setStyle(sf::Text::Underlined | sf::Text::Bold);
    else if (underLined && italicText)        txt.setStyle(sf::Text::Underlined | sf::Text::Italic);
    else if (boldText && italicText)          txt.setStyle(sf::Text::Bold | sf::Text::Italic);
    else if (underLined)                      txt.setStyle(sf::Text::Underlined);
    else if (boldText)                        txt.setStyle(sf::Text::Bold);
    else if (italicText)                      txt.setStyle(sf::Text::Italic);
}

void setSFMLTextOutlineColor(sf::Text &txt, float thickness, sf::Color color)
{
    txt.setOutlineColor(color);
    txt.setOutlineThickness(thickness);
}

void createSprite(sf::Texture &tex, sf::Sprite &spr, sf::Vector2f position, sf::Vector2f origin, bool smooth)
{
    #if defined(IS_ENGINE_SFML)
    tex.setSmooth(smooth);
    #endif
    spr.setTexture(tex);
    spr.setOrigin(origin.x, origin.y);
    is::setSFMLObjX_Y(spr, position.x, position.y);
}

void createSprite(sf::Texture &tex, sf::Sprite &spr, sf::IntRect rec, sf::Vector2f position, sf::Vector2f origin, bool repeatTexture, bool smooth)
{
    createSprite(tex, spr, position, origin, smooth);
    is::setSFMLObjTexRec(spr, rec.left, rec.top, rec.width, rec.height);
    #if defined(IS_ENGINE_SFML)
    if (repeatTexture) tex.setRepeated(true);
    #endif
}

void createSprite(sf::Texture &tex, sf::Sprite &spr, sf::IntRect rec, sf::Vector2f position, sf::Vector2f origin, sf::Vector2f scale, unsigned int alpha, bool repeatTexture, bool smooth)
{
    createSprite(tex, spr, rec, position, origin, repeatTexture, smooth);
    is::setSFMLObjScaleX_Y(spr, scale.x, scale.y);
    is::setSFMLObjAlpha(spr, alpha);
}

sf::Vector2f getCursor(sf::RenderWindow &window
                        #if defined(__ANDROID__)
                        , unsigned int finger
                        #endif // defined
                        )
{
    sf::Vector2i pixelPos =
    #if defined(__ANDROID__)
                            sf::Touch::getPosition(finger, window);
    #else
                            sf::Mouse::getPosition(window);
    #endif // defined

    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, window.getView());

    float dx = pointDistance(window.getView().getCenter().x, window.getView().getCenter().y,
                             worldPos.x, window.getView().getCenter().y);
    float dy = pointDistance(window.getView().getCenter().x, window.getView().getCenter().y,
                             window.getView().getCenter().x, worldPos.y);

    if (worldPos.x < window.getView().getCenter().x) dx *= -1;
    if (worldPos.y < window.getView().getCenter().y) dy *= -1;

    return sf::Vector2f(window.getView().getCenter().x + dx, window.getView().getCenter().y + dy);
}

short vibrate(short duration)
{
    #if defined(__ANDROID__)
    JNIEnv* env = (JNIEnv*)SDL_AndroidGetJNIEnv();
    jobject activity = (jobject)SDL_AndroidGetActivity();
    jclass clazz(env->GetObjectClass(activity));
    JavaVM* vm;
    env->GetJavaVM(&vm);

    // First, attach this thread to the main thread
    JavaVMAttachArgs attachargs;
    attachargs.version = JNI_VERSION_1_6;
    attachargs.name = "NativeThread";
    attachargs.group = NULL;
    jint res = vm->AttachCurrentThread(&env, &attachargs);

    if (res == JNI_ERR) return EXIT_FAILURE;

    // Retrieve class information
    jclass natact = env->FindClass("android/app/NativeActivity");
    jclass context = env->FindClass("android/content/Context");

    // Get the value of a constant
    jfieldID fid = env->GetStaticFieldID(context, "VIBRATOR_SERVICE", "Ljava/lang/String;");
    jobject svcstr = env->GetStaticObjectField(context, fid);

    // Get the method 'getSystemService' and call it
    jmethodID getss = env->GetMethodID(natact, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");
    jobject vib_obj = env->CallObjectMethod(activity, getss, svcstr);

    // Get the object's class and retrieve the member name
    jclass vib_cls = env->GetObjectClass(vib_obj);
    jmethodID vibrate = env->GetMethodID(vib_cls, "vibrate", "(J)V");

    // Determine the timeframe
    jlong length = duration;

    // Bzzz!
    env->CallVoidMethod(vib_obj, vibrate, length);

    // Free references
    env->DeleteLocalRef(vib_obj);
    env->DeleteLocalRef(vib_cls);
    env->DeleteLocalRef(svcstr);
    env->DeleteLocalRef(context);
    env->DeleteLocalRef(natact);
    env->DeleteLocalRef(clazz);

    // Detach thread again
    // this line is comment because it cause a bug
    // vm->DetachCurrentThread();
    #elif defined(IS_ENGINE_HTML_5)
    EM_ASM_ARGS({
                navigator.vibrate($0);
                }, duration);
    #else
    is::showLog("Vibrate Called ! Time : " + is::numToStr(duration) + " ms");
    #endif

    return 1; // EXIT_SUCCESS;
}

void openURL(const std::string& url, OpenURLAction action)
{
    std::string urlStr;
    switch(action)
    {
        case OpenURLAction::Http: urlStr = "http://" + url; break;
        case OpenURLAction::Tel: urlStr = "tel:" + url; break;
        default: urlStr = "mailto:" + url; break;
    }

#if defined(__ANDROID__)
    JNIEnv* env = (JNIEnv*)SDL_AndroidGetJNIEnv();
    jobject activity = (jobject)SDL_AndroidGetActivity();
    JavaVM* vm;
    env->GetJavaVM(&vm);

    vm->AttachCurrentThread(&env, NULL);

    // Retrieve class information
    jclass activityClass = env->FindClass("android/app/Activity");
    jclass intentClass = env->FindClass("android/content/Intent");
    jclass uriClass = env->FindClass("android/net/Uri");

    // convert URL std::string to jstring
    jstring uriString = env->NewStringUTF(urlStr.c_str());

    // call parse method
    jmethodID uriParse = env->GetStaticMethodID(uriClass, "parse", "(Ljava/lang/String;)Landroid/net/Uri;");

    // set URL in method
    jobject uri = env->CallStaticObjectMethod(uriClass, uriParse, uriString);

    // intent action
    jstring actionString =
        env->NewStringUTF((action != OpenURLAction::Tel) ? "android.intent.action.VIEW" : "android.intent.action.DIAL");

    // call the intent object constructor
    jmethodID newIntent = env->GetMethodID(intentClass, "<init>", "(Ljava/lang/String;Landroid/net/Uri;)V");

    // create the intent instance
    jobject intent = env->AllocObject(intentClass);

    // set intent constructor
    env->CallVoidMethod(intent, newIntent, actionString, uri);

    jmethodID startActivity = env->GetMethodID(activityClass, "startActivity", "(Landroid/content/Intent;)V");
    env->CallVoidMethod(activity, startActivity, intent);

    env->DeleteLocalRef(activityClass);
    env->DeleteLocalRef(intentClass);
    env->DeleteLocalRef(uriClass);
    env->DeleteLocalRef(intent);
    env->DeleteLocalRef(activity);
    //vm->DetachCurrentThread();
#elif defined(IS_ENGINE_HTML_5)
    std::vector<std::string> vectorArray;
    vectorArray.push_back(urlStr);

    EM_ASM_ARGS
    ({
        var vectorArray = new Module.VectorString($0);
        window.open(vectorArray.get(0));
    }, &vectorArray);
#else
    std::string op =
    #if !defined(SFML_SYSTEM_LINUX)
                     std::string("start ")
    #else
                     std::string("xdg-open ")
    #endif // defined
        .append(urlStr);
    system(op.c_str());
#endif // defined
}

#if defined(__ANDROID__)
std::string jstring2string(JNIEnv *env, jstring jStr)
{
    if (!jStr) return "";

    const jclass stringClass = env->GetObjectClass(jStr);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));

    size_t length = (size_t) env->GetArrayLength(stringJbytes);
    jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);

    std::string ret = std::string((char *)pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(stringClass);
    return ret;
}

std::string getDeviceId(JNIEnv *env, ANativeActivity *activity)
{
    jclass classActivity = env->FindClass("android/app/NativeActivity");
    jclass context = env->FindClass("android/content/Context");
    jclass telephony = env->FindClass("android/telephony/TelephonyManager");

    jfieldID field = env->GetStaticFieldID(context, "TELEPHONY_SERVICE", "Ljava/lang/String;");
    jobject staticField = env->GetStaticObjectField(context, field);

    jmethodID getSS = env->GetMethodID(classActivity, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");
    jobject objTel = env->CallObjectMethod(activity->clazz, getSS, staticField);
    jmethodID getId = env->GetMethodID(telephony, "getDeviceId", "()Ljava/lang/String;");
    jstring strId = (jstring)env->CallObjectMethod(objTel, getId);

    env->DeleteLocalRef(classActivity);
    env->DeleteLocalRef(context);
    env->DeleteLocalRef(telephony);
    return jstring2string(env, strId);
}

#endif
}
