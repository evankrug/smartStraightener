# MorphLibrary
An abstraction layer library for micro-controllers

## Philosophy  

There are multiple core ideals this library works with.

1. **Dynamic function assignment**

    The Morph Library is capable of dynamically assigning functions via function pointers. 
    
    Function pointers are used for configuration because they allow partial configurations without application-level side effects. This makes the development process easier when a new configuration needs to be written, as the whole configuration file does not have to be implemented, and non-implemented Morph function are simply non-functional. The functions can also be reconfigured during run-time, however effective usecases for run-time reconfiguration have not yet been found. 
    
    This feature can be turned off to support static function assignment. Configurations must be complete without this feature. 

    Using dynamic function assignment requires the software to configure itself at run-time. Static function assignment is more efficient in this regard. Recommend using dynamic function assignment during development, and switching to static function assignment for deployment. 

2. **Implementation details are defered to config level**

    The Morph Library makes no assumptions as to how the hardware interface functions. For this reason, it does not store information about any domain-level interactions. It also does not manage out-of-range values or other errors. These errors are expected to fail gracefully in the configuration level. Any information needed to perform the hardware level tasks are expected to be allocated in the configuration level.

3. **Morph functions are application-facing**

    This means that the function are written from an application level viewpoint, not a viewpoint that is necessarily easy for writing configurations. This allows the Morph Library to be easier to use and it doesn't cater to any one specific chipset. For example, setting an interrupt to trigger at a sepecific rate on an Atmel microcontroller is different from a PIC microcontroller. So, instead of finding a way to allow the user of the Morph Library to set register values, the Library instead defines common use-cases that can be implemented in configurations.  
    
4. **Morph Library does not guarantee hardware configuration**

    This essentially just means that the user of the Morph Library needs to be somewhat aware of the realities of embedded development. For example, setting a pin value to HIGH without first setting the pin direction will result in undefined behavior. This allows the library to be much more efficient as it does not have to configure the hardware with every function call.
