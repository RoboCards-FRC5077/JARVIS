#include "WPILib.h"

class Robot: public IterativeRobot
{

	RobotDrive myRobot;
	Joystick DriveStick, LiftStick;
	Victor LiftMotor;
	Compressor *c;
	LiveWindow *lw;
	int autoLoopCounter;

public:
	Robot() :
		myRobot(0, 1),
		DriveStick(0),
		LiftStick(5),
		LiftMotor(5),
		c(0),
		lw(NULL),
		autoLoopCounter(0)
	{
		myRobot.SetExpiration(0.1);
	}

private:
	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		c->SetClosedLoopControl(true);
	}

	void AutonomousInit()
	{
		autoLoopCounter = 0;
	}

	void AutonomousPeriodic()
	{
		if(autoLoopCounter < 100)
		{
			myRobot.Drive(-0.5, 0.0);
			autoLoopCounter++;
			} else {
			myRobot.Drive(0.0, 0.0);
		}
	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		myRobot.ArcadeDrive(DriveStick.GetY(), -DriveStick.GetX());
		if(LiftStick.GetRawButton(1))
		{
			LiftMotor.Set(1.0);
		}
		else if(LiftStick.GetRawButton(2)){
			LiftMotor.Set(-0.5);
		}
		else{
			LiftMotor.Set(0.0);
		}
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
