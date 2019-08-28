# ElementLibrary
A Morph Library companion that implements application-level interfaces. 

## Setup steps (Atmel Studio):

1. Create a new solution
2. Clone this library and the morph library into the root of the repository.
3. In AtmelStudio File > Add... > Existing Project 
    * If the platform is the SAMD platform navigate to MorphLibrary/MorphLibrary-SAMD/MorphLibrary-SAMD.cproj
    * If the platform is the AVR platform navigate to MorphLibrary/MorphLibrary/MorphLibrary.cproj
4. Under your project, there is a "Libraries" folder. Right Click > Add Library > Project Libraries > Check MorphLibrary > OK

5. Clone the configurations into your project. These steps are getting around limitations of AtmelStudio. Just bear with me:
    1. create a folder in your project called "MorphConfigurations"
    2. In the terminal navigate to \<Atmel Studio Solution Name\>/\<Atmel Studio Project Name\>/
    3. Clone the configurations repo into the directory. This should clone into the folder created earlier.
    4. Return to Atmel Studio. Right click on the "MorphConfigurations" folder > Add... > Existing Item > Select everything in the MorphConfigurations folder > Add

6. In the Solution Explorer right-click on your project > Properties > Toolchain
    * Navigate to Symbols > Defined symbols > Add > Add the symbol for the platform being targeted. 
        * This symbol should be documented wherever you retreived the configuration.
    * Navigate to Directories:
        * Add the Element include directory: ElementLibrary/src/include
        * Add the Morph include directory: MorphLibrary/MorphLibrary/include (This is the same on both platforms)
    * Navigate to Libraries > Library search path (-L):
        * If the platform is the SAMD platform add MorphLibrary/MorphLibrary-SAMD        
        * If the platform is the AVR platform add MorphLibrary/MorphLibrary

7. The Morph Library is now setup. Now, setup the Element Library.
   * Add a new folder to your project named "Element"
   * Navigate into the new folder, and create another folder named "include".
   * On "include", Right click > Add > Existing Item... > Navigate to ElementLibrary/src/include and select everything in the folder > Add as Link.
   * On "Element", Right click > Add > Existing Item... > Navigate to ElementLibrary/src and select everything in the folder > Add as Link.
   
ElementLibrary is now ready to use.
