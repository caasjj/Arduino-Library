#ifndef PID_h
#define PID_h
#define LIB_VERSION	0.0.1

class PID
{

  public:

  //Constants
  #define ENABLED	1
  #define DISABLED	0

  
    PID(double);  
	
    bool Configure(double);   

    void SetLoopConstants(float, float, float);                   

    void UpdateLoop(double); 
											  
	void SetOutputLimits(double, double);

	void Enable(bool);							  
										
	//void SetDataUploadCallback( void (*)  );
				  
	void EnableDataUpload( bool );

	double GetKp();						 
	double GetKi();
	double GetKd();	
	int GetMode();	
	int GetDirection();

  private:
	void _initialize();
	
	double dispKp;				// * we'll hold on to the tuning parameters in user-entered 
	double dispKi;				//   format for display purposes
	double dispKd;				//
    
	double kp;                  // * (P)roportional Tuning Parameter
    double ki;                  // * (I)ntegral Tuning Parameter
    double kd;                  // * (D)erivative Tuning Parameter

	int controllerDirection;

    double *myInput;              // * Pointers to the Input, Output, and Setpoint variables
    double *myOutput;             //   This creates a hard link between the variables and the 
    double *mySetpoint;           //   PID, freeing the user from having to constantly tell us
                                  //   what these values are.  with pointers we'll just know.
			  
	unsigned long lastTime;
	double ITerm, lastInput;

	unsigned long SampleTime;
	double outMin, outMax;
	bool inAuto;

};
#endif

