// Configuration file for the Element Library

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include <MorphTypes.h>
#include <MorphUtils.h>

#ifndef ELEMENT_CONFIG_H
#define ELEMENT_CONFIG_H

//--Button Configuration Begin--//

// Element Direct Button Support
// A "Direct" button is a normal button, one button is one GPIO pin.
// Other button types are: 
//    1. "VoltDiv" which use 
//       voltage division to determine the button pressed.
//       This is read off a 
//
//    2. "Capacitive" which use capacitive touch to determine
//       the button touched.
//
enum ElementButtonEvent {ElementButtonEventDown, ElementButtonEventUp, ElementButtonEventPress, ElementButtonEventShort, ElementButtonEventLong};

#define ELEMENT_DIRECT_BUTTON_SUPPORT

#ifdef ELEMENT_DIRECT_BUTTON_SUPPORT

    // Button support is enabled. 

    #define ELEMENT_DIRECT_BUTTON_DEBOUNCE_TIME_MS 10

    #define ELEMENT_DIRECT_BUTTON_SHORT_HOLD_TIME_MS 2000

    #define ELEMENT_DIRECT_BUTTON_LONG_HOLD_TIME_MS 5000
	
	#define ELEMENT_MAXIMUM_NUM_BUTTONS 10

	#define ELEMENT_MAXIMUM_NUM_COMBOS 10
	
	#define MAXIMUM_BUTTONS_PER_COMBO 3
	
	typedef struct element_button_combo_struct{
		int8_t combo_id;
		MorphTimeValue hold_time; // How long does this button combo need to be held?
		uint8_t num_buttons; // How many buttons are involved?
		int8_t button_ids[MAXIMUM_BUTTONS_PER_COMBO]; // This array holds all of the buttons involved in the combo.
		void (*combo_callback)(void);
		bool combo_callback_reg;
		bool combo_event_triggered;
	} ElementButtonComboConfig;

    // This struct lays out all button behavior.
    typedef struct element_button_config_struct{
        MorphPinNumber button_pin_number;
		int8_t button_id; // The ID of the button. Used to reference to it elsewhere.
        enum MorphPinValue  button_depressed_value;
        enum MorphPinPullState button_default_pull;
		bool button_signaled;
		MorphTimeValue button_signaled_time;
		bool button_stabilized;
        void (*button_down_callback)(void);
        bool button_down_callback_reg;
		bool button_down_event_triggered;
        void (*button_up_callback)(void);
        bool button_up_callback_reg;
		bool button_up_event_triggered;
        void (*button_press_callback)(void);
        bool button_press_callback_reg;
		bool button_press_event_triggered;
		void (*button_short_callback)(void);        
        bool button_short_callback_reg;
		bool button_short_event_triggered;
		void (*button_long_callback)(void);
        bool button_long_callback_reg;
		bool button_long_event_triggered;
	} ElementButtonConfigStruct;

	typedef struct element_direct_button_group_struct{
		uint8_t cur_num_buttons;
		ElementButtonConfigStruct element_button_config_array[ELEMENT_MAXIMUM_NUM_BUTTONS];	
		uint8_t cur_num_combos;
		ElementButtonComboConfig element_button_combo_config_array[ELEMENT_MAXIMUM_NUM_COMBOS];
	} ElementDirectButtonGroup;
	
	static ElementDirectButtonGroup element_master_direct_button_group =
	{
		.cur_num_buttons = 0,
		.element_button_config_array = {0},
		.cur_num_combos = 0,
		.element_button_combo_config_array = {0}
	};
 

#endif

//--Button Configuration End--//

//--Animation System Configuration Begin--//

	#define ELEMENT_ANIMATION_ENGINE_MAXIMUM_BUFFERS 5
	#define ELEMENT_ANIMATION_ENGINE_CONCURRENT_ANIMATION_MAX 5
	
	enum ElementAnimationEngineStatus {Animation_Engine_Success = 0, 
									   Animation_Engine_Failure = 1, 
									   Animation_Engine_Update_Complete = 2, 
									   Animation_Engine_Partial_Update = 3,
									   Animation_Engine_Animation_Complete = 4};

	// NOTE: If you try to do some weird bit_depth you MUST pack all the data in a continuous row major fashion.
	// C will not take care of this for you. (as you probably know).
	typedef struct element_calculated_animation_instance_struct{
		uint8_t alpha_mask;				// Assumes only up to 8 bits will be used for alpha. If more are necessary, you're insane.  
		uint8_t framerate;				// The framerate of the animation.
		uint8_t * frames;				// Pointer to an array of frames.
		uint16_t num_frames;			// The number of frames in the animation.
		uint32_t frame_size;			// This is the size of the frames (in bytes). This is so the engine can address correctly.
		uint16_t data_dimensions[2];	// The size of the x/y coordinates in terms of bit-depth.
		uint16_t dimension_offsets[2];	// The offset for the data. This is used to overlay small graphics onto larger buffers, for example.
		uint8_t bit_depth;				// The number of bits per pixel.
		bool is_running;				// Is the animation running?
		MorphTimeValue start_time;		// The time this animation started (Used to calculate the current frame)
		MorphTimeValue offset_time;		// This pads the beginning of the animation with blank frames with full alpha until a certain time.
		uint16_t current_frame;			// The current frame. Used to pause/unpause animations.	
		bool is_repeating;				// Should this animation repeat?
	} ElementCalculatedAnimationInstance;
 
    typedef struct element_functional_animation_instance_struct ElementFunctionalAnimationInstance;

	typedef struct element_animation_instance_struct{
		uint8_t animation_id;
		bool is_calculated;				// Is this struct for a calculated or functional animation?
		ElementCalculatedAnimationInstance * cal_anim;
		ElementFunctionalAnimationInstance * fun_anim;
	} ElementAnimationInstance;

	// These types of structs represent frame buffers. 
	// There may be multiple buffers necessary throughout the application.
    typedef struct element_animation_config_buffer_struct{
		uint8_t buffer_id;
		uint8_t * buffers;				// Array of all the buffers.
		uint8_t * write_buffer;         // The buffer currently being written to.
		uint8_t * read_buffer;			// The buffer currently being read from.
		uint8_t num_buffers;			// Number of buffers that are being used for swapping.
		uint8_t bit_depth;				// The number of bits used for one "pixel".
		uint32_t buffer_size;			// The size of one buffer in bytes.
		uint16_t data_dimensions[2];	// The size of the x/y coordinates in terms of bit-depth.
		ElementAnimationInstance * current_animations[ELEMENT_ANIMATION_ENGINE_CONCURRENT_ANIMATION_MAX];
		uint8_t current_animation_size;
    } ElementAnimationBufferConfigStruct;

	struct element_functional_animation_instance_struct{
		enum ElementAnimationEngineStatus (*function)(ElementAnimationBufferConfigStruct*);			 // The function pointer that will be called for this animation.
	};

	// This is the top level struct. 
	// This struct type manages all of its children.
	typedef struct element_animation_engine_config_struct{
		uint8_t maximum_animation_buffers;
		uint8_t current_animation_buffers;
		ElementAnimationBufferConfigStruct * animation_buffers[ELEMENT_ANIMATION_ENGINE_MAXIMUM_BUFFERS];
	} ElementAnimationEngineConfig;

	// This is the only top-level struct the Element library supports.
	// All children will be added to this one. 
	static ElementAnimationEngineConfig animation_engine_config = 
	{
		ELEMENT_ANIMATION_ENGINE_MAXIMUM_BUFFERS,
		0,
		{
			NULL // Initialize the animation buffers to null.
		}
	};

//--Animation System Configuration End--//


//--Clock Configuration Begin--//

	typedef struct element_date_time_struct{
		int16_t year;
		int16_t month;
		int16_t day;
		int16_t hour;
		int16_t minute;
		int16_t second;
		int16_t millisecond;
	} ElementDateTime;


	typedef struct element_clock_config_struct{
		MorphTimeValue rtc_val;
		ElementDateTime date;
	} ElementClockConfig;


	static ElementClockConfig clock_master_config =
	{
		0,
		{
			2019,
			0,
			1,
			0,
			0,
			0,
			0,
		}
	};

//--Clock Configuration End--//

// --Thermistor Configuration Begin-- //

#define THERMISTORS_MAX_COUNT	5
#define THERMISTOR_CONTROLLERS_MAX_COUNT	5
#define THERMISTOR_TEMP_HISTORY 5

	enum ElementThermistorEvent {ElementThermistorHigh, ElementThermistorLow, ElementThermistorDirectCallback};

	typedef struct element_thermistor_config_struct{
		MorphPinNumber pin;
		MorphADCResolution res; // Used for initializing the ADC. Only useful if the hardware can change resolutions.
		enum MorphADCReference ref; // Which reference type are we using?
		uint8_t ref_id; // Which reference of that type are we using?
		uint16_t prescaler_value;
		int32_t series_resistor_value;
		float valid_low; // The valid lowest temperature for this thermistor.
		float valid_high; // The valid highest temperature for this thermistor.
		float nominal_temp; // The normal temperature for this thermistor.
		float nominal_resistance; // The normal temperature for this thermistor.		
		float beta; // The beta coefficient of the thermistor.
		float current_temp; // The last calculated temperature for this thermistor.
		float history[THERMISTOR_TEMP_HISTORY]; // The previous raw temperature measurements. 
		uint8_t filter_array_loc;
		uint8_t filter_array_size;
	} ElementThermistor;
	
	typedef enum element_thermistor_controller_type {ElementThermistorOnOffControl, ElementThermistorPIDControl} ElementThermistorControllerType;

	typedef struct element_thermistor_control_struct{
		ElementThermistorControllerType type;
		ElementThermistor * thermistor;
		bool active; // Should this controller be controlling currently?
		float setpoint;
	} ElementThermistorController;
	
	typedef struct element_thermistor_pid_control_struct ElementThermistorPIDController;
	
	typedef struct element_thermistor_pid_control_struct{
		ElementThermistorController super;
		float rate;      // The frequency at which to run the controller. Is floating point to support > 1 second update rates.
		MorphTimeValue last_update; // The last time the controller was updated.
		bool cap_integral;  // Should the integral be capped?
		float max_integral; // Variable to cap integral at.
		// Process variables.
		float cur_integral;   // The current integral. 
		float cur_derivative; // The current derivative.
		// Tuning variables.
		float P_coef;
		float I_coef;
		float D_coef;		
		float previous_process_variable; // We need to save a bit of history for the derivative.
		float control_output_bias; // Bias for output. This is used for debucking.
		float control_output;
		void (*control_callback)(ElementThermistorPIDController * ); // Callback to apply control. 
		bool control_callback_reg;
		
	} ElementThermistorPIDController;

	typedef struct element_thermistor_on_off_control_struct{
		ElementThermistorController super;
		float hysteresis_range;
		// Forward hysteresis will heat until it reaches setpoint + hysteresis_range, then let the temp fall to the setpoint.
		// If this is false, reverse hysteresis will be performed. Heating will be performed until setpoint, then fall to setpoint - hysteresis_range.
		bool forward_hyst; 
		bool one_shot; // One-shot mode will only call the callbacks one time per set-point side.
		bool control_direction_up; // If this is true, we are going up. If this is false, we are going down.
		void (*temp_high_callback)(void); // This callback will be performed when the max temp is reached.
		bool temp_high_callback_reg;
		bool temp_high_callback_triggered;
		void (*temp_low_callback)(void); // This callback will be performed when the min temp is reached.
		bool temp_low_callback_reg;
		bool temp_low_callback_triggered;		
	} ElementThermistorOnOffController;
	
	// This struct is meant to be used as a stack to track all active thermistors.
	typedef struct element_thermistor_system_config{
		uint8_t thermistor_count;
		uint8_t controller_count;
		ElementThermistor * thermistors[THERMISTORS_MAX_COUNT];
		ElementThermistorController * thermistor_controllers[THERMISTOR_CONTROLLERS_MAX_COUNT];
	} ElementThermistorSystemConfig;


	static ElementThermistorSystemConfig master_thermistor_system_config = 
	{
		0, // There are zero thermistors at start.
		0, // There are zero controllers at start.
		{
			NULL // All pointers are initialized to NULL.
		},
		{
			NULL // All pointers are initialized to NULL.
		}	
	};

// --Thermistor Configuration End-- //
 
// --Timer Configuration Begin-- //

#define TIMERS_MAX_COUNT	10

enum ElementTimerEvent {ElementTimerDone, ElementTimerPaused, ElementTimerCanceled};

typedef struct element_timer_config_struct{
	MorphTimeValue start_time; // The time we started the timer.
	MorphTimeValue total_duration; // This simply saves the overall duration.
	MorphTimeValue remaining_duration; // This is the duration of the current "run", for example, pausing the timer and starting will start a new "run".
	bool is_running;
	bool is_done;
	bool is_canceled; 
	bool is_paused;
	void (*done_callback)(void);
	bool done_callback_reg;
	bool done_callback_triggered;
	void (*paused_callback)(void);
	bool paused_callback_reg;
	bool paused_callback_triggered;
	void (*canceled_callback)(void);
	bool canceled_callback_reg;
	bool canceled_callback_triggered;
} ElementTimer;

typedef struct element_timer_system_config_struct{
	uint8_t current_timer_count;
	ElementTimer * timer_array[TIMERS_MAX_COUNT]
} ElementTimerSystemConfig;

static ElementTimerSystemConfig master_timer_config = {
	0,
	{
		NULL
	}
};

// --Timer Configuration End-- //

// --Variable Watch Configuration Begin -- //

typedef enum element_variable_types_enum {ElementBool, 
										  ElementUInt8, 
										  ElementUInt16, 
										  ElementUInt32, 
										  ElementUInt64,
										  ElementInt8, 
										  ElementInt16, 
										  ElementInt32, 
										  ElementInt64,
										  ElementFloat,
										  ElementDouble} ElementVariableType;

typedef enum element_variable_match_types {MatchEqual,
										   MatchNotEqual,
										   MatchGreater,
										   MatchGreaterOrEqual,
										   MatchLess,
										   MatchLessOrEqual} ElementVariableMatchType;

typedef struct element_variable_watch_config_struct{
	ElementVariableType type; // The type that is being evaluated.
	ElementVariableMatchType match_type; // How should the two variables be evaluated?
	uint64_t raw_match_data;  // The data that will be matched.
	uint8_t * point_data;	  // The pointer to the changing variable. This is uint8_t for the finest pointing granularity. 
};

// --Variable Watch Configuration End -- //

#endif

