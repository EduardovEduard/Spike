Please build libleveldb by yourself

# Linux
just get source from 

# Android
```
git clone https://github.com/litl/android-leveldb.git
cd library/jni
```
fix Application.mk as follows:
```
APP_PLATFORM=android-14
APP_ABI := armeabi 
APP_STL := gnustl_static
```
then compile:
```
cd /library
ndk-build
```
and copy everything from obj/local/ 
NOTE: there are also `armeabi-v7a mips x86` platforms

# IOS
TODO:

