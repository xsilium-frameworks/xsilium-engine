set(OIS_SRC 
  src/OISEffect.cpp
  src/OISException.cpp
  src/OISForceFeedback.cpp
  src/OISInputManager.cpp
  src/OISJoyStick.cpp
  src/OISKeyboard.cpp
  src/OISObject.cpp
  src/extras/LIRC/OISLIRC.cpp
  src/extras/LIRC/OISLIRCFactoryCreator.cpp
)

if (APPLE)
	set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/src/OISInputManager.cpp PROPERTIES COMPILE_FLAGS "-x objective-c++")
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CMake/OISSettings.in ${CMAKE_CURRENT_BINARY_DIR}/OISSettings.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(OIS_HDR
  includes/OISConfig.h
  includes/OISEffect.h
  includes/OISEvents.h
  includes/OISException.h
  includes/OISFactoryCreator.h
  includes/OISForceFeedback.h
  includes/OIS.h
  includes/OISInputManager.h
  includes/OISInterface.h
  includes/OISJoyStick.h
  includes/OISKeyboard.h
  includes/OISMouse.h
  includes/OISMultiTouch.h
  includes/OISObject.h
  includes/OISPrereqs.h
	${CMAKE_CURRENT_BINARY_DIR}/OISSettings.h
)


if (WIN32)

	set(OIS_BUILD_WIN32 FALSE)
	if (XSILIUM_OIS_WIN32_NATIVE)
		set(OIS_BUILD_WIN32 TRUE)
	else ()
		if (NOT DirectX_FOUND)
			set(OIS_BUILD_WIN32 TRUE)
		endif()
	endif()
	
	if (NOT OIS_BUILD_WIN32)
		set(OIS_PLAT 
    		includes/win32/Win32ForceFeedback.h
    		includes/win32/Win32InputManager.h
    		includes/win32/Win32JoyStick.h
    		includes/win32/Win32KeyBoard.h
    		includes/win32/Win32Mouse.h
    		includes/win32/Win32Prereqs.h
    		src/win32/Win32ForceFeedback.cpp
    		src/win32/Win32InputManager.cpp
    		src/win32/Win32JoyStick.cpp
    		src/win32/Win32KeyBoard.cpp
    		src/win32/Win32Mouse.cpp
    		src/win32/extras/WiiMote/hiddevice.cpp
    		src/win32/extras/WiiMote/OISWiiMote.cpp
    		src/win32/extras/WiiMote/OISWiiMoteFactoryCreator.cpp
    		src/win32/extras/WiiMote/OISWiiMoteForceFeedback.cpp
    		src/win32/extras/WiiMote/OISWiiMoteRingBuffer.cpp
    		src/win32/extras/WiiMote/wiimote.cpp
			)
		link_libraries(${DirectX_DXGUID_LIBRARY} ${DirectX_DINPUT8_LIBRARY} ${DirectX_XINPUT_LIBRARY})
	else ()
		set(OIS_PLAT 
			includes/win32native/Win32NativeInputManager.h
			includes/win32native/Win32NativeJoystick.h
			includes/win32native/Win32NativeKeyboard.h
			includes/win32native/Win32NativeMouse.h
			includes/win32native/Win32NativePrereqs.h
			src/win32native/Win32NativeInputManager.cpp
			src/win32native/Win32NativeKeyboard.cpp
			src/win32native/Win32NativeJoystick.cpp
			src/win32native/Win32NativeMouse.cpp
			)
	endif ()

endif()


if (APPLE) 
	if (XSILIUM_BUILD_IPHONE)
		#add_definitions(-DOIS_IPHONE_PLATFORM)
		set(OIS_PLAT
			includes/iphone/iPhoneAccelerometer.h
			includes/iphone/iPhoneHelpers.h
			includes/iphone/iPhoneInputManager.h
      			includes/iphone/iPhoneMultiTouch.h
      			includes/iphone/iPhonePrereqs.h

      			src/iphone/iPhoneAccelerometer.mm
      			src/iphone/iPhoneInputManager.mm
      			src/iphone/iPhoneMultiTouch.mm
		)
	else()
		set(OIS_PLAT 
			includes/mac/CocoaInputManager.h
     			includes/mac/CocoaJoyStick.h
      			includes/mac/CocoaKeyBoard.h
      			includes/mac/CocoaMouse.h
      			includes/mac/CocoaHelpers.h
      			includes/mac/MacHelpers.h
      			includes/mac/MacHIDManager.h
      			includes/mac/MacInputManager.h
      			includes/mac/MacJoyStick.h
      			includes/mac/MacKeyboard.h
      			includes/mac/MacMouse.h
      			includes/mac/MacPrereqs.h

			src/mac/CocoaInputManager.mm
      			src/mac/CocoaJoyStick.mm
      			src/mac/CocoaKeyBoard.mm
      			src/mac/CocoaMouse.mm
      			src/mac/MacHelpers.cpp
      			src/mac/MacHIDManager.cpp
      			src/mac/MacInputManager.cpp
      			src/mac/MacJoyStick.cpp
      			src/mac/MacKeyboard.cpp
      			src/mac/MacMouse.cpp
		)
	endif()
	
	if (IOKit_FOUND)
		link_libraries(${IOKit_LIBRARIES})
	endif()
elseif (UNIX)
	if (XSILIUM_BUILD_ANDROID)
		set(OIS_PLAT
			includes/android/AndroidInputManager.h
			
			src/android/AndroidInputManager.cpp
		)   
	else () 		
		set(OIS_PLAT 
			includes/linux/EventHelpers.h
			includes/linux/LinuxForceFeedback.h
			includes/linux/LinuxInputManager.h
			includes/linux/LinuxJoyStickEvents.h
			includes/linux/LinuxKeyboard.h
			includes/linux/LinuxMouse.h
			includes/linux/LinuxPrereqs.h

			src/linux/EventHelpers.cpp
			src/linux/LinuxForceFeedback.cpp
			src/linux/LinuxInputManager.cpp
			src/linux/LinuxJoyStickEvents.cpp
			src/linux/LinuxKeyboard.cpp
			src/linux/LinuxMouse.cpp
		)
	endif()
endif()

include_directories(${XSILIUM_OIS_INCLUDE} )
add_library(OIS ${OIS_SRC} ${OIS_HDR} ${OIS_PLAT})

config_target_if_iphone_build(OIS TRUE)
