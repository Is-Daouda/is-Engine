#include "GameFunction.h"

namespace is
{
void showLog(std::string str)
{
    #if !defined(__ANDROID__)
    std::cout << str.c_str() << "\n";
    #else
    #if defined(ENABLE_SHOW_LOG)
    __android_log_print(ANDROID_LOG_DEBUG, "LOG_INFO", "%s\n", str.c_str());
    #endif
    #endif // defined
}

bool isBetween(float a, float b, float c)
{
 if (b <= c)
 return (b <= a and a <= c) ;
 else
 return (c <= a and a <= b) ;
}

void setSFMLTextAlpha(sf::Text &obj, unsigned int alpha, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b)
{
    obj.setFillColor(sf::Color(r, g, b, alpha));
}

void setSFMLTextColor(sf::Text &obj, sf::Color color)
{
    obj.setFillColor(color);
}

void setSFMLTextOutlineColor(sf::Text &obj, sf::Color color)
{
    obj.setOutlineColor(color);
}

void setSFMLRecAlpha(sf::RectangleShape &obj, unsigned int alpha, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b)
{
    obj.setFillColor(sf::Color(r, g, b, alpha));
}

void setSFMLRecColor(sf::RectangleShape &obj, sf::Color color)
{
    obj.setFillColor(color);
}

/*
bool isCrossing(float l1, float r1, float l2, float r2)
{
    if (is::isBetween(l1, l2, r2))      return true;
    else if (is::isBetween(r1, l2, r2)) return true;
    else if (is::isBetween(l2, l1, r1)) return true;
    else return false;
}

bool isCollision(Rectangle r1, Rectangle r2)
{
    return
    (
        isCrossing(r1.m_left, r1.m_right, r2.m_left, r2.m_right) and
        isCrossing(r1.m_top, r1.m_bottom, r2.m_top, r2.m_bottom)
    );
}

bool isCollision(Rectangle r, Point p)
{
    return
    (
        is::isBetween(p.x, r.m_left, r.m_right) and
        is::isBetween(p.y, r.m_top, r.m_bottom)
    );
}

bool isCollision(Point p, Rectangle r)
{
    return isCollision(r, p);
}

bool isCollision(Rectangle r, Line l)
{
    Line l1(r.m_left, r.m_top, r.m_right, r.m_top);
    Line l2(r.m_left, r.m_top, r.m_left, r.m_bottom);
    Line l3(r.m_right, r.m_top, r.m_right, r.m_bottom);
    Line l4(r.m_left, r.m_bottom, r.m_right, r.m_bottom);

    Point p(l.x1, l.y1);

    if (isCollision(r, p))       return true;
    else if (isCollision(l1, l)) return true;
    else if (isCollision(l2, l)) return true;
    else if (isCollision(l3, l)) return true;
    else if (isCollision(l4, l)) return true;
    else return false;
}

bool isCollision(Line l, Rectangle r)
{
    return isCollision(r, l);
}

bool isCollision(Line l1, Line l2)
{
    Point a(l1.x1, l1.y1);
    Point b(l1.x2, l1.y2);
    Point c(l2.x1, l2.y1);
    Point d(l2.x2, l2.y2);

    if (side(a, c, d) * side(b, c, d) > 0)      return false;
    else if (side(c, a, b) * side(d, a, b) > 0) return false;
    else return true;
}
*/

int sign(float x)
{
    if (x > 0.f)      return 1;
    else if (x < 0.f) return -1;
    else return 0.f;
}

int side(Point m, Point a, Point b)
{
    Point ab(b.m_x - a.m_x, b.m_y - a.m_y);
    Point am(m.m_x - a.m_x, m.m_y - a.m_y);
    float vectoriel = ab.m_x * am.m_y - am.m_x * ab.m_y;
    return sign(vectoriel);
}

bool collisionTest(Rectangle const &firstBox, Rectangle const &secondBox)
{
    if (firstBox.m_bottom <= secondBox.m_top)    return false;
    if (firstBox.m_top    >= secondBox.m_bottom) return false;
    if (firstBox.m_right  <= secondBox.m_left)   return false;
    if (firstBox.m_left   >= secondBox.m_right)  return false;
    return true;
}

float pointDistance(float x1, float y1, float x2, float y2)
{
    float X = x1 - x2;
    float Y = y1 - y2;
    return sqrt(X * X + Y * Y);
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

void createRectangle(sf::RectangleShape &rec, sf::Vector2f recSize, sf::Color color, float x, float y, bool center)
{
    rec.setSize(recSize);
    rec.setFillColor(color);
    if (center) rec.setOrigin(rec.getGlobalBounds().width / 2, rec.getGlobalBounds().height / 2);
    rec.setPosition(x + rec.getGlobalBounds().width / 2, y + rec.getGlobalBounds().height / 2);
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

void createText(sf::Font const& fnt, sf::Text &txt, std::string const &text, float x, float y, int txtSize, bool underLined, bool boldText, bool italicText)
{
    txt.setFont(fnt);

    if (txtSize != 0) txt.setCharacterSize(txtSize);
    else txt.setCharacterSize(20);
    textStyleConfig(txt, underLined, boldText, italicText);
    txt.setFillColor(sf::Color(0, 255, 0));
    txt.setString(text);
    txt.setOrigin(txt.getGlobalBounds().width / 2, txt.getGlobalBounds().height / 2);
    txt.setPosition(x + txt.getGlobalBounds().width / 2, y + txt.getGlobalBounds().height / 2);
}

void createText(sf::Font const& fnt, sf::Text &txt, std::string const &text, float x, float y, sf::Color color, int txtSize, bool underLined, bool boldText, bool italicText)
{
    txt.setFont(fnt);

    if (txtSize != 0) txt.setCharacterSize(txtSize);
    else txt.setCharacterSize(20);
    textStyleConfig(txt, underLined, boldText, italicText);
    txt.setFillColor(color);
    txt.setString(text);
    txt.setOrigin(txt.getGlobalBounds().width / 2, txt.getGlobalBounds().height / 2);
    txt.setPosition(x + txt.getGlobalBounds().width / 2, y + txt.getGlobalBounds().height /2);
}

void createText(sf::Font const& fnt, sf::Text &txt, std::string const &text, float x, float y, sf::Color color, sf::Color outlineColor, int txtSize, bool underLined, bool boldText, bool italicText)
{
    txt.setFont(fnt);

    if (txtSize != 0) txt.setCharacterSize(txtSize);
    else txt.setCharacterSize(20);
    textStyleConfig(txt, underLined, boldText, italicText);
    txt.setFillColor(color);
    txt.setOutlineColor(outlineColor);
    txt.setOutlineThickness(1.f);
    txt.setString(text);
    txt.setOrigin(txt.getGlobalBounds().width / 2, txt.getGlobalBounds().height / 2);
    txt.setPosition(x + txt.getGlobalBounds().width / 2, y + txt.getGlobalBounds().height /2);
}

void createSprite(sf::Texture &tex, sf::Sprite &spr, sf::Vector2f position, sf::Vector2f origin, bool smooth)
{
    tex.setSmooth(smooth);
    spr.setTexture(tex);
    spr.setOrigin(origin.x, origin.y);
    spr.setPosition(position.x + origin.x, position.y + origin.y);
}

void createSprite(sf::Texture &tex, sf::Sprite &spr, sf::IntRect rec, sf::Vector2f position, sf::Vector2f origin, bool repeatTexture, bool smooth)
{
    tex.setSmooth(smooth);
    spr.setTexture(tex);
    spr.setTextureRect(rec);
    if (repeatTexture) tex.setRepeated(true);
    spr.setOrigin(origin.x, origin.y);
    spr.setPosition(position.x + origin.x, position.y + origin.y);
}

void createSprite(sf::Texture &tex, sf::Sprite &spr, sf::IntRect rec, sf::Vector2f position, sf::Vector2f origin, sf::Vector2f scale, unsigned int alpha, bool repeatTexture, bool smooth)
{
    tex.setSmooth(smooth);
    spr.setTexture(tex);
    spr.setTextureRect(rec);
    if (repeatTexture) tex.setRepeated(true);
    spr.setOrigin(origin.x, origin.y);
    spr.setPosition(position.x + origin.x, position.y + origin.y);
    spr.setScale(scale.x, scale.y);
    spr.setColor(sf::Color(255, 255, 255, alpha));
}

#if defined(__ANDROID__)
void setScreenLock(bool disableLock)
{
    // First we'll need the native activity handle
    ANativeActivity *activity = sf::getNativeActivity();

    // Retrieve the JVM and JNI environment
    JavaVM* vm = activity->vm;
    JNIEnv* env = activity->env;

    // First, attach this thread to the main thread
    JavaVMAttachArgs attachargs;
    attachargs.version = JNI_VERSION_1_6;
    attachargs.name = "NativeThread";
    attachargs.group = NULL;
    vm->AttachCurrentThread(&env, &attachargs);

    // Retrieve class information
    jclass classActivity = env->FindClass("android/app/NativeActivity");
    jclass context = env->FindClass("android/content/Context");
    jclass classKeyMg = env->FindClass("android/app/KeyguardManager");
    jclass classKeyLock = env->FindClass("android/app/KeyguardManager$KeyguardLock");

    jfieldID fieldKeyGuard = env->GetStaticFieldID(context, "KEYGUARD_SERVICE", "Ljava/lang/String;");
    jobject staticField = env->GetStaticObjectField(context, fieldKeyGuard);

    jmethodID getSS = env->GetMethodID(classActivity, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");
    jobject keyguardManager = env->AllocObject(classKeyMg);
    jobject objKeyguardManager = env->CallObjectMethod(activity->clazz, getSS, staticField);
    keyguardManager = objKeyguardManager;

    jmethodID newKeyguardLockId = env->GetMethodID(classKeyMg, "newKeyguardLock", "(Ljava/lang/String;)Landroid/app/KeyguardManager$KeyguardLock;");
    jobject lock = env->AllocObject(classKeyLock);
    jobject objKeyguardLock = env->CallObjectMethod(keyguardManager, newKeyguardLockId, staticField);
    lock = objKeyguardLock;

    std::string actionString = "disableKeyguard";
    if (!disableLock) actionString = "reenableKeyguard";
    jmethodID functKeyguardID = env->GetMethodID(classKeyLock, actionString.c_str(), "()V");
    env->CallVoidMethod(lock, functKeyguardID);

    // Detach thread again
    vm->DetachCurrentThread();
}

int vibrate(sf::Time duration)
{
    // First we'll need the native activity handle
    ANativeActivity *activity = sf::getNativeActivity();

    // Retrieve the JVM and JNI environment
    JavaVM* vm = activity->vm;
    JNIEnv* env = activity->env;

    // First, attach this thread to the main thread
    JavaVMAttachArgs attachargs;
    attachargs.version = JNI_VERSION_1_6;
    attachargs.name = "NativeThread";
    attachargs.group = NULL;
    jint res = vm->AttachCurrentThread(&env, &attachargs);

    if (res == JNI_ERR)
        return EXIT_FAILURE;

    // Retrieve class information
    jclass natact = env->FindClass("android/app/NativeActivity");
    jclass context = env->FindClass("android/content/Context");

    // Get the value of a constant
    jfieldID fid = env->GetStaticFieldID(context, "VIBRATOR_SERVICE", "Ljava/lang/String;");
    jobject svcstr = env->GetStaticObjectField(context, fid);

    // Get the method 'getSystemService' and call it
    jmethodID getss = env->GetMethodID(natact, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");
    jobject vib_obj = env->CallObjectMethod(activity->clazz, getss, svcstr);

    // Get the object's class and retrieve the member name
    jclass vib_cls = env->GetObjectClass(vib_obj);
    jmethodID vibrate = env->GetMethodID(vib_cls, "vibrate", "(J)V");

    // Determine the timeframe
    jlong length = duration.asMilliseconds();

    // Bzzz!
    env->CallVoidMethod(vib_obj, vibrate, length);

    // Free references
    env->DeleteLocalRef(vib_obj);
    env->DeleteLocalRef(vib_cls);
    env->DeleteLocalRef(svcstr);
    env->DeleteLocalRef(context);
    env->DeleteLocalRef(natact);

    // Detach thread again
    // this line is comment because it cause a bug
    // vm->DetachCurrentThread();
    return EXIT_SUCCESS;
}

void openURl(std::string urlStr)
{
    ANativeActivity *activity = sf::getNativeActivity();
    JNIEnv *env = activity->env;
    JavaVM* vm = activity->vm;

    vm->AttachCurrentThread(&env, NULL);

    // Retrieve class information
    jclass activityClass = env->FindClass("android/app/Activity");
    jclass intentClass = env->FindClass("android/content/Intent");
    jclass uriClass = env->FindClass("android/net/Uri");

    // convert URL std::string to jstring
    urlStr = "http://" + urlStr;
    jstring uriString = env->NewStringUTF(urlStr.c_str());

    // call parse method
    jmethodID uriParse = env->GetStaticMethodID(uriClass, "parse", "(Ljava/lang/String;)Landroid/net/Uri;");

    // set URL in method
    jobject uri = env->CallStaticObjectMethod(uriClass, uriParse, uriString);

    // intent action
    jstring actionString = env->NewStringUTF("android.intent.action.VIEW");

    // call the intent object constructor
    jmethodID newIntent = env->GetMethodID(intentClass, "<init>", "(Ljava/lang/String;Landroid/net/Uri;)V");

    // create the intent instance
    jobject intent = env->AllocObject(intentClass);

    // set intent constructor
    env->CallVoidMethod(intent, newIntent, actionString, uri);

    jmethodID startActivity = env->GetMethodID(activityClass, "startActivity", "(Landroid/content/Intent;)V");
    env->CallVoidMethod(activity->clazz, startActivity, intent);

    env->DeleteLocalRef(activityClass);
    env->DeleteLocalRef(intentClass);
    env->DeleteLocalRef(uriClass);
    env->DeleteLocalRef(intent);

    vm->DetachCurrentThread();
}

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
