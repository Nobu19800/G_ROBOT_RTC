// -*- C++ -*-
/*!
 * @file  G_ROBOT.cpp
 * @brief G-ROBOT Control Component
 * @date $Date$
 *
 * @author 宮本　信彦　n-miyamoto@aist.go.jp
 * 産業技術総合研究所　ロボットイノベーション研究センター
 * ロボットソフトウエアプラットフォーム研究チーム
 *
 * LGPL
 *
 * $Id$
 */

#define _USE_MATH_DEFINES
#include <math.h>

#include "G_ROBOT.h"



// Module specification
// <rtc-template block="module_spec">
static const char* g_robot_spec[] =
  {
    "implementation_id", "G_ROBOT",
    "type_name",         "G_ROBOT",
    "description",       "G-ROBOT Control Component",
    "version",           "1.0.0",
    "vendor",            "AIST",
    "category",          "Controller",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
	// Configuration variables
	"conf.default.servo_num", "20",
	"conf.default.port", "COM3",
	"conf.default.default_motion_time", "300",

	// Widget
	"conf.__widget__.servo_num", "text",
	"conf.__widget__.port", "text",
	"conf.__widget__.default_motion_time", "text",
	// Constraints
	"conf.__constraints__.default_motion_time", "0<x<10000",

	"conf.__type__.servo_num", "int",
	"conf.__type__.port", "string",
	"conf.__type__.default_motion_time", "int",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
G_ROBOT::G_ROBOT(RTC::Manager* manager)
    // <rtc-template block="initializer">
	: RTC::DataFlowComponentBase(manager),
	m_target_angleIn("target_angle", m_target_angle),
	m_motion_timeIn("motion_time", m_motion_time),
	m_current_angleOut("current_angle", m_current_angle)

    // </rtc-template>
{
	G_ROBO = NULL;
}

/*!
 * @brief destructor
 */
G_ROBOT::~G_ROBOT()
{
}



RTC::ReturnCode_t G_ROBOT::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
	addInPort("target_angle", m_target_angleIn);
	addInPort("motion_time", m_motion_timeIn);

	// Set OutPort buffer
	addOutPort("current_angle", m_current_angleOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("servo_num", m_servo_num, "20");
  bindParameter("port", m_port, "COM3");
  bindParameter("default_motion_time", m_default_motion_time, "300");
  // </rtc-template>
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t G_ROBOT::onFinalize()
{
	if (G_ROBO)
	{
		delete G_ROBO;
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t G_ROBOT::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t G_ROBOT::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t G_ROBOT::onActivated(RTC::UniqueId ec_id)
{
	if (G_ROBO == NULL)
	{
		G_ROBO = new GR001((char *)m_port.c_str());
		if (G_ROBO->connect() < 0){
			std::cerr << "Error: can't find G-Robot: " << m_port << std::endl;
			return RTC::RTC_ERROR;
		}
		if (G_ROBO->startThread() == 0){
			std::cerr << "Error: fail to create thread" << std::endl;
			return RTC::RTC_ERROR;

		}

	}
	else
	{
		if (G_ROBO->connect() < 0){
			std::cerr << "Error: can't find G-Robot: " << m_port << std::endl;
			return RTC::RTC_ERROR;
		}
	}

	G_ROBO->setServo(1, 0);
	G_ROBO->setDefaultMotionTime(m_default_motion_time);
	G_ROBO->initPosition();

	m_target_angle.data.length(m_servo_num);

  return RTC::RTC_OK;
}


RTC::ReturnCode_t G_ROBOT::onDeactivated(RTC::UniqueId ec_id)
{
	G_ROBO->setServo(0, 1);
	G_ROBO->closePort();
	
  return RTC::RTC_OK;
}


RTC::ReturnCode_t G_ROBOT::onExecute(RTC::UniqueId ec_id)
{
	if (m_motion_timeIn.isNew())
	{
		m_motion_timeIn.read();
		G_ROBO->setMotionTime(m_motion_time.data);
	}
	if (m_target_angleIn.isNew())
	{
		m_target_angleIn.read();
		for (int i = 0; i < m_target_angle.data.length(); i++)
		{
			if (i < m_servo_num)
			{
				double angle = m_target_angle.data[i] * 180.0 / M_PI;

				G_ROBO->setJoint(i + 1, angle * 10);

				//std::cout << i << "\t" << angle * 10 << std::endl;
			}
			

		}
		G_ROBO->startMotion();
	}
	/*for (int i = 0; i < m_servo_num; i++)
	{
		m_out.data[i] = G_ROBO->getAngle(i+1);
		
	}
	setTimestamp(m_out);
	m_outOut.write();*/
  return RTC::RTC_OK;
}


RTC::ReturnCode_t G_ROBOT::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t G_ROBOT::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t G_ROBOT::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t G_ROBOT::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t G_ROBOT::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void G_ROBOTInit(RTC::Manager* manager)
  {
    coil::Properties profile(g_robot_spec);
    manager->registerFactory(profile,
                             RTC::Create<G_ROBOT>,
                             RTC::Delete<G_ROBOT>);
  }
  
};


