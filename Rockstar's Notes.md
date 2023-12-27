# Overview

RAGE code provides and supports basic functionality that all projects at Rockstar San Diego can build on. However, no one game takes advantage of all of RAGE’s capabilities. RAGE is intended to provide a cross-platform abstraction layer for many common pieces of functionality that most games will require. Each specific game should select only the RAGE functionality that they need. In turn, RAGE should not contain game-specific code.

RAGE is not intended to be a complete "turn-key" game development engine, though as more general-purpose elements are migrated from games down into RAGE, it could move in this direction.

The qualification for code being part of RAGE is that it provide functionality which most projects need, at least as a starting point. It is strongly recommended that projects link directly with the RAGE modules, rather than taking copies of the RAGE code and putting their own version into their project-specific code hierarchy. 
RAGE shares nuts-and-bolts functionality, production tools, and advanced solutions commonly needed by all games. RAGE thereby gets new projects started more quickly, minimizes redundant development, standardizes tools and processes, and provides the most advanced game technology to all RSD projects. Also, RAGE supplies an abstraction layer between a project's API and platform-specific hardware, which allows project programmers to work in a mostly platform-independent way despite developing for multiple platforms. 
By design, RAGE provides capabilities that our specific projects can use directly, or as a foundation to build on through inheritance. Hence, most RAGE subsystems are low-level and platform-independent, and provide ubiquitous necessities like matrix transforms and basic rendering. However, some subsystems are mid- or high-level, and provide advanced but commonly needed capabilities like support for vehicles and creatures. 
Dependencies between subsystems have been minimized, so RAGE can be used in full or in part, as the needs of your project dictate. This modular approach helps us optimize, extend, or replace subsystems and their components with ease, in direct response to the specific needs of current projects. Also, future projects can get started more quickly by inheriting these ongoing advances. 

As a summary of a summary, the following list provides a high altitude snapshot of RAGE's scope and capabilities. The next section, "Highlights of Selected Systems," takes a closer look at the capabilities of a few key components of RAGE:  
 - Management of Graphics: 
 - Management of texture memory. 
 - Management of graphics states (e.g. blend modes, active texture, Z buffer mode, and much more) 
 - Management of viewport states (e.g. current transform matrices, view volumes, visual culling techniques, and much more) 
 - Management of lighting states (e.g. active material, per-light parameters, and much more) 
 - Support of robust shader functionality 
 - Management of precomputed display lists 
 - Transformation, lighting, clipping, and dynamic re-texturing of precomputed and dynamic geometry 
 - Management of input/output for gamepads, memcards, and other devices 
 - Support of in-game tuning that can be saved and iterated upon 
 - Support of advanced creature functionality (e.g. skinned skeletons, playback of multiple animation channels with blending, inverse kinematics, and forward dynamics) 
 - Support of highly optimized physics for general and vehicular applications (e.g. detection of collisions, calculation of impact forces, contact physics, and management of numerous objects) 
 - Support of core audio functionality (e.g. multiple audio sample streams, midi, and 2D and 3D sound objects)

A complete description of the capabilities of RAGE would require several hundred pages...

Retain Mode (RM) provides faster and more feature-complete lighting, shading, and rendering  
 - to let artists create more sophisticated materials, with multi-texture effects and other visual richness, entirely through data; 
 - to support the reading of platform-independent "mesh" files that contain robust descriptions of models and their properties, and are easier to experiment with than old-style model files; 
 - to add the notion of a more complex, feature-complete model class than RAGE had before. 

The classes in RM are layered as follows:  
 - A model is a collection of shader indices and geometries. RM provides an extra level of indirection on shader assignment to allow for two important improvements: 
 - You can easily render a set of models with a completely different set of materials by swapping only a single pointer. 
 - Multiple models (at different levels of detail, or from different parts of a complex object like a car) can all be defined in terms of the same material bindings. 
 - An LOD group is a collection of model lists (up to four in total), with encoded LOD switch points. Based on a high-detail base model, each LOD can consist of multiple models at progressively lower levels of detail.

Not every LOD needs the same number of models. This capability of RM allows objects like cars to turn off suspensions or even individual wheels, in favor of baking them into the parent model at simpler levels of detail. Skinned objects always have exactly zero or one model per level of detail. 
 - A shader group is an array of shaders. The shaders are defined using a simple language that allows you to specify one or more passes per material.
 - A drawable is an LOD group combined with a list of shader groups. The drawable knows about all possible variants of the shaders (palette swaps or texture swaps), and also knows about all per-instance CPV data, if any.
 
The drawable is the fundamental unit of loading, which simplifies load-ordering issues because we know all models, instance CPV data, and relevant textures will be loaded at the exact same time. 
The state system underlying RM uses lazy evaluation to eliminate unnecessary state changes. Furthermore, since the entire system has a richer notion of a model, it's possible for the implementation to do a global sort by texture (if necessary) to improve rendering performance. 

The PS2, GC, and Xbox have different graphics hardware pipelines and associated APIs. To facilitate the production and display of optimal artwork in this context, RAGE includes a cross-platform shader technology. The goal of this technology is to provide artists with a comprehensive set of shaders, with which to describe the visual aspects of artwork more accurately and provocatively. 
 From the standpoint of art, the artists only need to define the RAGE shader attributes once in Maya, and not worry about each individual platform. Behind the scenes, each shader is optimized on a per-platform basis to provide the best possible implementation on all hardware.  
 - For increased versatility, objects can contain multiple shaders, organized into groups. Shader groups can be swapped during gameplay, allowing for different rendering styles and customized effects. For example, a new off-road vehicle can collect dust, mud, and damage as gameplay progresses. 
 - 3D modeling packages like Maya have many solutions to accomplish the same rendering task. To cut down on the potential bugs introduced from shader conflicts, RAGE shaders are fully tested, qualified, and stable before introducing them into production. Since there is only a single simple definition of a given shader, and never two solutions for a single rendering effect, the potential for visual bugs is minimized. 
 
From the standpoint of technology, the RAGE shader sets up graphics states as a comprehensive part of the rendering phase. To accomplish this in the most versatile way, the RAGE shader can receive inputs from many sources outside of itself -- including UV animations tied to game input and triggers, lighting values from virtually any source (including hard-coded directly into the shader), and even behavioral scripts.
Shaders can be classified by speed, texture count, rendering passes, instruction count, resource usage, and so forth. The RAGE shader allows different categories of effects to be combined simultaneously, so artists can achieve a versatile range of visual effects with less cost. Here is a subset of the types of shading techniques supported by RAGE: 
 - Dynamically lit polygons uses global lights, local lights, and specular highlights. Example: vehicles with headlights moving through a crowded city at night. 
 - Shadow / light maps simulates the casting of intricate shadows over simple geometry. Example: variable lighting in a forest. 
 - Reflection mapping provides realistic metallic and wet surfaces that reflect their surroundings. Example: Player vehicles in MC2. 
 - Emboss / Bump mapping simulates 3D variations in surfaces of low LOD objects. Examples: rocky roads, brick buildings, stone walls, alligator skin, wrinkles in clothing. 
 - Projected and Self-Shadows allows moving objects to cast shadows dynamically onto complex geometry. 
 - Shadow Volumes define an area of shadow that moving objects can pass through. Example: a car going under a bridge. 
 - Volumetric Fog: simulates swamp fog that gets thicker closer to the ground, and patches of fog that varies randomly in density. 
 - Texture mapping with algorithms: Modifying texture maps dynamically according to polynomial and sinusoidal functions can achieve effects way beyond the simple linear animation of textures. Examples: flowing rivers and lava. 
 - Displacement maps are another supported approach to adding 3D surface detail to such things as rocky surfaces and wrinkled faces. 
 - Multiple Texture Blending beyond light and shadow mapping. Examples: corrugated effect on metal walls; adding dirt and mud and chipped paint to surface of off-road cars in response to gameplay. 

The RAGE Physics subsystem greatly outperforms commercial middleware, in terms of speed, memory efficiency, features, adaptability, and usability. See the following topics table for summaries of the specific capabilities of RAGE physics.   

Collision detection code determines whether or not two objects have come into contact with each other. In addition to detecting dynamic collisions, this code is also commonly used by AI, cameras, and targeting systems for pathfinding, determination of line of sight, and the movement of cameras. 
Objects can be made up of one or more of the following types of primitives:  
 - Point  
 - Line segment  
 - Sphere  
 - Swept sphere  
 - Box  
 - Domed cylinder  
 - Polygonal geometry (including concave shapes)  
 - Polygonal terrain  
 - Spline terrain  
 - Spline road  
 - Cloth  
 - Fluid  
 - Force field (e.g., explosions)
   
Additionally, objects may be constrained by joints, springs, and damping forces. Specific objects and types of objects can also be flagged to enable or disable collision detection with other specific objects and types of objects.   

 A sophisticated set of routines determines how two objects will interact, based on information gained from collision detection, and the answers to the following questions:  
 - Where should impact forces be applied? 
 - What impact forces should be applied? 
 - How do physical properties of the two objects affect impact forces? 
 - Is the collision force enough to cause an object to break, and how many pieces will the object break into? 
 - If objects are interpenetrating, how should they be separated? 
 After answering these questions, the code for calculating impacts applies the correct forces to each object involved in the collision.  

After objects collide, it is necessary to keep track of continuing contacts, in order to allow them to properly come to rest. Contact physics is composed of a series of routines that maintain all information about contacts between active objects, and modify reactions in an appropriate manner. 
For example, when a car hits a mailbox, the mailbox bounces down the street according to a series of impact calculations. The force applied by the car to the mailbox starts a series of forces applied by the road to the bouncing mailbox. Due to collision damping, the mailbox eventually comes to rest according to the routines in contact physics code. 

 The Object Manager maintains large numbers of objects efficiently, which involves the following specific responsibilities:  
 - Manage interactions between active objects. 
 - Ensure that distant objects are not tested against each other.  
 - Ensure that inactive objects are not tested against each other.  
 - Initialize objects upon activation.  
 - Deactivate objects upon coming to rest.  
 - Load/save/optimize proprietary object file formats. 
 - Break composite objects into individual components.

The RAGE Vehicle subsystem supports a wide variety of wheeled vehicles, from off-road buggies to street racers, motorcycles, odd-wheeled vehicles, and 18-wheeler trucks. By simulating literally hundreds of components of vehicles, the Vehicle subsystem provides extensive control over in-game tuning. Game designers can achieve results ranging from full simulation to total arcade. The Vehicle subsystem also ties the tunable properties of vehicles to cutting edge graphical and audio effects.  

The RAGE Vehicle subsystem is architected to provide game designers with extensive access to vehicular properties via tuning parameters. Game designers can access these parameters in real-time on the target platform, via the following hierarchy of widgets, to extensively customize the properties of vehicles, to dramatically affect the player's experience during gameplay:  
 - Simulation includes parameters for computing vehicular movements (acceleration, braking, cornering, etc.) based on the physical properties of the vehicle and forces acting upon it.

Tunable properties are organized into the following sub-banks of widgets, each of which contains numerous widgets: 
 - Car: physical properties like weight and distribution of mass. 
 - Aero: aerodynamics forces like drag and damping. 
 - Fluid: buoyancy forces, in case the vehicle ends up in the drink! 
 - Engine: engine stuff like horsepower and RPMs. 
 - Trans: transmission properties like number of gears and gear ratios. 
 - Drivetrain: parameters for how efficiently the drivetrain transfers the engine's power to the wheels, etc. 
 - Wheel: parameters for the suspension, braking, steering, and tire performance. 
 - Axle: simulation of front/rear torsion bars. 
 - Gyro includes parameters for orienting a vehicle while it's in the air, drifting in a turn, executing a spin out, and riding a wheelie. If the vehicle has only two wheels, the Gyro parameters apply the gyroscopic effects characterizing a motorcycle in motion. 
 - Stuck defines the conditions in which a vehicle is considered stuck, and when the game should get the vehicle un-stuck automatically. 
 - Damage includes parameters for tuning a vehicle's durability, and activating visual effects associated with damage (smoke, particles). 

 Vehicle ties into various graphical effects -- including: suspensions that articulates dynamically, tires that motion blur, particle effects that kick up gravel, and damage effects with visual and functional facets. 
 
 Vehicle ties into various audio effects -- including engine sounds, driving sounds (wind and road noise, for example), tire skidding sounds, and suspension noises. 

 The RAGE Creature subsystem provides cutting edge power and flexibility to handle all next-gen applications we could imagine.Creature's key capabilities are summarized in the following topic table.
 - General-purpose skeletons with rotational, translation, quaternion, scale, and user definable DOFs 
 - Formats for flexible animation channels -- including raw floating point data, compressed fixed-point data, or key-framed channel data 
 - Animation mapping system capable of easily defining animations that only affect a subset of the DOF in a skeleton 
 - Articulated accessories with animations synchronized to main creature animations 
 - General-purpose animation blending and state machine -- including guidelines on how to design new game-specific animation drivers 
 - General purpose IK solver 
 - Optimized limb-specific IK solvers 
 - Support in locomotion system for using IK to lock feet on ground 
 - Support in environment interaction system for locking hands and other end-effectors to objects in the environment 
 - IK goals and blend values can be animated like any other channel 
 - Skinning (both simple and blended) 
 - Level of detail (LOD) 
 - Support for textural, palette, and geometric variants 
 - High quality lighting and materials 
 - Full body morphing (e.g. skeleton, skin, texture) 
 - Facial animation using blended morph targets 
 - Support for lip-sync 
 - Support for facial motion capture 
 - Support for animation data generated by Puppet Works' Voice Works, a Maya plugin that analyzes the phonemes of the voice audio file and lays down keys that can easily be edited in Maya by the animator. 
 - Standard Maya character rigs and rigging process 
 - Support Mel scripts 
 - Support the process for incorporating lip-sync and motion capture 
 - Robust export process 
 - Documentation and examples 
 - Collision detection 
 - Ragdoll dynamics (including blending to and from animation, and limiting dynamics to a subset of the skeleton) 
 - Clothing 
 - Hooks for audio 
 - Standardized approach to using creatures in cinematics 

 The RAGE Sound subsystem provides an underlying implementation and low-level interface for audio. This audio API is easy to use and totally cross-platform. Key capabilities:  
 - Load wave and midi data to the hardware. 
 - Play, stop, pause, resume and query the status of the hardware. 
 - Set volume, pitch, pan, and all other basic audio functions for playback on the hardware. 

The actual sound data is platform specific, and needs to be created using the appropriate tool for each platform. to keep the application calls from having to be changed from platform to platform, however, the application loads and organizes the data in a similar manner on all platforms, and provides audio programmers with a generic API for accessing and manipulating that data. 

 Support for gamepads and joysticks is relatively simple and available, but current middleware has little or no support for memory cards on consoles. The RAGE Input subsystem provides robust support for memory cards, and includes the following capabilities:  
 - Uses an asynchronous architecture to store and manage data on memory cards, and provides and easy-to-access data packaging system, to maximize the use of hardware. 
 - Insulates programmers from platform-specific oddities, through a high level API that's fully platform-independent. This dramatically simplifies coding for memory card systems on different platforms. 
 - Can carry out the save and load process while game levels load and gameplay is taking place, within the constraints of the platform's TRC requirements. This avoids the need for pausing gameplay, and allows game designers to fully utilize the game saving capability that's available for each machine. 
 - Supports multi-tap functionality on memory card devices attached to peripherals. 
 - Allows for easy customizing of the needs of individual platforms, without influencing the other platforms. To facilitate this need, programmers can derive a specific memcard class and add any custom functions to it. 

 The established RAGE system for resource management has proven itself on many of our recent games, including several of our current projects. For new projects, RAGE created an alternative system using heap resourcing. Both systems have similar benefits:  
 - Allows for loading large amounts of resources at once. This saves the time needed to decide which assets to load, and avoids the need to make multiple loading calls. By reducing seek times and consolidating loads, this system speeds up disk access and load times. 
 - Supports streaming.   

 RAGE's traditional approach to resource management allocates resources at the level of individual classes. Its distinctive qualities include:  
 - Resources objects in a modular way, allowing you to mix and match the loading of objects as needed to support game testing. For example, you could switch out characters into a given level without having to regenerate large resource files for every combination of characters. 
 - Requires an understanding of pointers in low-level code, but doesn't require as much high-level understanding of overall memory layout.   

The RAGE Heap Resourcing System tackles the resourcing problem from a very different perspective. It allows a program to redirect all its essential allocations to a specific heap, called a "package." The package has helper methods to save and retrieve the pointers of previous allocations. Restoring this heap on a subsequent run of the program accomplishes everything you did up front in one quick step. In the process, you regain easy access to the contents of a package, should you want to save or manipulate it further.

The heap approach to resourcing has the following distinctive qualities:  
 - Does not require rewriting lots of code to gain its benefits. Can be retrofit into existing code quickly and easily. 
 - The packaged nature of the resources make swapping packages easier. 
 - Does not require a deep understanding of how it works at a low level, but does require an awareness of overall memory layout. Does not work with objects 

Here's a list of the supported RAGE configurations:
 - Debug : use this configuration if you want to use a debugger, see all asserts, and use the widget banks. Optimization and inlining code is off.   
 - ToolDebug : Almost the same configuration as the Debug configuration except that the _TOOL #define is on, and __PAGING is off. Intended for offline tools and exporters.                
 - Beta : use this configuration if you want to see all asserts,use the widget banks, but be able to run the game at an acceptable frame rate. Optimizations and inlining code are on, which makes source-level debugging more difficult.    
 - PreRelease : Use this configuration if you want to debug a release build. All debug information is available and and optimizations and inlining code is off.                                    
 - Release : use this configuration if you want to see a version as close as possible to the final build. There is no debug information, and optimizations and code inlining is on.         
 - ToolRelease : Almost the same configuration as the Releaseconfiguration except that the _TOOL #define is on, and __PAGING is off. Intended for offline tools and exporters.                
 - Profile : The same configuration as the Release configuration except that the program has debug information and the __PROFILE #define is on. It also links with CallCap "instrumented" libraries on Xenon.              
 - Final : Almost the same configuration as the Release configuration except that this configuration is intended to be the version that would ship on a gold master game disc. Many ASCII loaders and all noncritical TTY output is compiled out, and the game engine always assumes it's booting from a disc.               

Each RAGE module contains one or more "project" files (filename.vcproj) and "workspace" files (filename.sln), alongside the source code itself. When you check out the version of RAGE code that's appropriate for your project, you also get the project and workspace files that accompany that code.
You should make sure that you set the environment variable RAGE_DIR if you wish to compile RAGE code.  RAGE_DIR should point to the toplevel RAGE directory itself, not the parent of the /rage/ directory.
We intentionally don't assume rage is part of RAGE_DIR so that you can have numbered rage releases living next to each other and switch between them easily.
Rockstar San Diego uses ..\\..\\..\\..\\rage for our RAGE_DIR so that we can extract a RAGE tree anywhere and have it just work.
A project (vcproj) file defines standardized build configurations (e.g. Win32 Release and many others) containing the headers and source code you want included in a particular "project."
Note: The term "project" is used here to refer to a collection of related header and source files, typically in one module, that are meant to build together.

The directory for each RAGE module generally contains one project file for the whole module, and one project file for each tester with an associated workspace.
 - Testers are always dependent on the current module, and can be dependent on other RAGE modules and remote modules beyond RAGE. 
 - The dependencies for a tester take the form of links to project (vcproj) files in dependent modules. Since each project file lists the header and source files in that project, a single link to a project file effectively links to potentially numerous header and source files.
 - As with project files, Autowiz generates workspace (sln) files from the data you put in Makefiles.
 - When you wish to edit code, you can open the workspace file for the tester that incorporates that code, instead of opening individual .h and .cpp files. The workspace gives you convenient access to all files that the tester depends on.
 - Updating Project and Workspace Files
 
When you modify existing RAGE code, you usually don't need to update project and workspace files.  You only need to regenerate these files when
 - adding or removing RAGE header, implementation, or tester files 
 - changing the dependencies of a tester 
 - testing your code locally with special build configurations and/or dependencies. 

Never edit project and workspace files directly, or through Visual Studio! Only update project and workspace files by running Autowiz on a per-module basis. Before running Autowiz, however, you may need to edit the Makefile in each module being updated.
 - Adding and Removing Files to RAGE Modules *

Use the procedure described in this topic to add (or remove) RAGE modules, header files, implementation files, and testers. You can also use this procedure to define or modify tester dependencies.
The procedure below creates or updates appropriate project (vcproj) and workspace (sln) files, to incorporate your changes:
 - Close your workspace.
 - Edit the makefile.bat file in the module you modified. (For details, see "Editing Makefiles".)
 - Open a command prompt. Go to the directory of the module containing modified files.  Run aw.bat or ..\\..\\build\\genproj.bat in the directory you modified.
 - If you modified code in more than one module, repeat this procedure for the other modified modules.
 - If you need to regenerate all project files (usually necessary only when the templates have been updated with a change you want) then run rage/build/genprojall.bat. 
Note: This procedure assumes you have a <c>c:/pcbuild/bin</c> directory set up on your PC and in your PATH environment variable.

If the environment variable SCCPROVIDER set, Source control is added to the vcproj (in front of the guid line) - 
as it would be if you add source control in visual studio. If the variable is not set - source control information is not added. 
This variable should be added to the system-variables.  Do not set this environment variable if you do not have source control integrated into Visual Studio.

Every active RAGE module contains exactly one makefile.bat
\file. This Makefile defines the dependencies and
environmental variables that Autowiz uses to create and
update project (dsp or vcproj) and workspace (dsw or sln)
files for that module. Whenever you add or remove RAGE
modules and files, or need to define or modify tester
dependencies, edit the following environmental variables in
the Makefiles for the affected modules:

The FILES, HEADONLY, and CODEONLY variables also support
folder creation; place the folder name before the file name,
separated by a colon. See rage/base/src/system/makefile.bat
for an example.

Here's a list of environment variables that are declared in
build\\genproj.bat that you can use in makefile.bat. These
are useful for testers, but you should probably explicitly
list out what RAGE libraries you need in your game project.

Environment             Description
 - RAGE_AI_LIBS     Contains a list of RAGE artificial intelligence libraries such as ainav, aicore, aiveh, etc.
 - RAGE_CORE_LIBS   Contains a list of RAGE core libraries that most libraries are dependent on like file, system, atl, etc.
 - RAGE_GFX_LIBS    Contains a list of RAGE graphics libraries such as grmodel, grcore, crskeleton, etc.
 - RAGE_NET_LIBS    Contains a list of RAGE networking libraries such as net_engine, net2, etc.
 - RAGE_PH_LIBS     Contains a list of RAGE physics libraries such as physics, phinertia, phbound, etc.
 - RAGE_AUD_LIBS    Contains a list of RAGE audio libraries such as audiocommand, audiocontrol, audiodriver,etc.

At Rockstar San Diego, virtually all code is done in C++ and assembler. We don't necessarily use all of the capabilities of C++, and in fact there are certain things which we intentionally try to avoid.

When creating any code, and particularly shared code like RAGE, please follow the guidelines in this topic, unless you have a good reason not to. Shared code becomes easier to share and maintain if format and usage are consistent throughout. Although we have a very open culture that encourages creative expression, shared code is not the best place to insist on expressing your stylistic idiosyncrasies.

Also, when you edit other people's code, please respect the format and usage that's already in place — unless you're taking responsibility for that code henceforth, in which case you should update it to match these guidelines. Similarly, all code in a module should use a consistent style (ideally in accordance with these guidelines).

Module Name               Prefix
------------------------  ------
atl                       at
bank                      bk
cranimation               cra
crskeleton                crs
devcam                    dcam
diag                      diag
file                      file
grcore                    grc
input                     io
math                      mth (?)
mesh                      msh  
paging                    pg
profile                   pf
rmcore                    rmc
string                    str (?)
system                    sys (?)
vector                    vec        

The RAGE resourcing system operates by taking snapshots of
memory during a normal ASCII load and dumping them directly
to disk. The memory image can then be reloaded and fixed up
much more quickly than the standard loading paths because
there's no parsing or reformatting overhead.

Resourcing is a prerequisite for streaming; however, anything
that has been successfully resourced can usually be made
streamable with little additional effort. Essentially our
streaming system is an asynchronous resource loader with a
fixed page size.

There are several advantages of resourcing:
 - It's fast. Fixups are typically cheap and your entire
    level load can be one giant disk read.
 - It avoids dynamic memory allocation; you can simply stop
    using an object and load another resource on top of it.
 - It allows you to eliminate extra loading code and data
    from your final application (typically a few hundred
    kilobytes).
 - Resources can be either loaded asynchronously or
    streamed.
 - Resources save a small amount of memory, because there
    are no internal memory nodes (typically 16 bytes) between
    each allocation.

There are, of course, several disadvantages as well:
 - If you're constantly regenerating resources because
    you're iterating or tuning data, it's actually a little
    slower because you pay the round-trip cost of writing the
    finished resource heap back out to disc and then reading it
    back in again. Projects typically have special command-line
    \options to disable portions of resourcing to work around
    this.
 - It's fragile if you're not careful. If a programmer makes
    nontrivial changes to any data structures that were used in a
    particular resource, they've *got* to remember to bump the
    resource version number so that the users will automatically
    regenerate new resources (note that one useful trick is to
    have the version number be the sum of both a master version
    number and sizeof several key data structures to make this a
    little less error-prone). They can also expose asset pipeline
    \bugs where new data is not propagated properly along with
    new code.
	
Okay, here's the really ugly secret of the resource system --
dumping memory to disk and reading it back in again is only
going to work if the memory is read into the exact same
address. Some companies handle this by reserving fixed blocks
in high memory to hold their resources so that they can
guarantee this address will never change. If we were
programming in C instead of C++, we could probably stop right
here and be done with it. But the problem is that classes
containing any virtual functions will contain a virtual
pointer, which is a pointer to a table of function pointers;
even the slightest changes to our code will cause some or all
virtual pointers to move slightly and invalidate all existing
resources.

So our solution is to adopt the notion of a resource
constructor. A resource constructor is a non-default
constructor which accepts a datResource& object. This object
contains fixup information (namely, the difference between
the memory address the resource was originally built at and
the address it's being relocated to).

So there are two major advantages to having resource
constructors:
 - Objects are relocatable across builds or even during
    runtime.
 - Virtual functions can work reliably even after code
    changes. In fact, you can even add additional virtual
    functions to a class without invalidating existing resources.
    (Note that if you make a class virtual that was not
    previously, you will invalidate existing resources because the
    size of the class will have changed).
	
When you call pgPaging::LoadBuild, internally it does something like this: 
```
void *buffer = new char[size_of_resource];
datResource rsc(buffer, (int)buffer-(int)original_address,size_of_resource);
Read(buffer,size_of_resource);
Object *T = (Object*) buffer;
T-\>Place(rsc);
```

RAGE currently uses the standard memory allocation services
provided by the underlying platform although this will likely
change in the future.

All Win32 Debug builds will dump leaks to the debug output
window on shutdown. To diagnose a leak, add -breakonalloc=NNN
(where NNN is the number in curly braces) to the
command line and run under the debugger. Adding new command
line switches (including -breakonalloc itself!) will
throw subsequent allocation id's off (because the Microsoft
startup code uses malloc) so run with -breakonalloc=0
first to stabilize the id's.

Namespaces should precede script names, global procedures and
global variables. Namespaces should generally be in the three
to four letter range and be in lowercase. For example:
* rage = Rage (Rockstar Advanced Game Engine)
* rage = Rockstar San Diego
* pong = Pong game
* mc3 = Midnight Club 3 game

The following namespaces are depricated and should not be
used any more:
* rsd = Rockstar San Diego
* age = AGE (Angel studios Game Engine)
* rst = Rockstar Shader Tool
* rex = Rage EXporter

When designing your scripts, it’s always important to think
about modularity, extensibility and maintenance. With that it
mind, it’s often a good idea to keep your procedures
tractable by limiting them to 50 lines. You can, of course,
exclude any comments or blank lines from this limit. While
this is not a rigid standard, it’s generally the case that
procedures can become too convoluted when they are over 50
lines.

The Xbox 360 is a very complex machine and optimizing for it
can be tricky. IBM and Microsoft did a good job at making a
very fast machine for very specific code. The Xbox 360 is not
a generic computer. It is not very suitable for running
traditional PC style code. A lot of 'tricks' that were
\optimizations on PCs and/or previous consoles may actually
be slower than just doing it without any tricks. Try to stick
basic implementations as you are coding, don't try anything
fancy for speed. Often times the basic code that may be
viewed as 'slow' is actually the most optimal.

The hardware itself is very compartmentalized and is designed
for several things to function in isolation at the same time.
There are 3 cores on the Xbox 360 cpu and 2 hardware threads
\on each core for a total of 6 hardware threads. Each
hardware thread has its own register set. Each core has its
\on 32kb L1 data cache and its own 32kb L1 instruction cache.
All three cores share one 1mb L2 data cache. Take advantage
\of threads as much as possible. If you can, plan your game
to use the hardware threads in parallel. If you structure
your game using the traditional single threaded model you end
up using only 1/6th of the CPU power on the machine.

Load hit stores are by far the largest waste of time on the
Xenon. A load-hit store occurs when the CPU loads from an
address that it wrote to within the last ~40 cycles. When a
load-hit store occurs the CPU stalls for 40+ cycles. The
length of the stall is dependent on memory latency to the
address in question. Load-hit stores can almost always be
avoided making this a complete waste of 40+ cycles. Now I
realize that ~40 cycles may not sound like a large cost on a
CPU with 5.3 million cycles per frame, but when you have
80,000 load hit stores in your frame you waste 3.2 million
cycles. For a 16.67 millisecond frame, you would be spending
about 10 milliseconds stalled on load-hit stores.

The easiest way to find load-hit stores is using tracedump.
Most load-hit stores can be removed by simply moving things
around in the code so the compiler can do a better job at
scheduling.

Floating point branches are very costly on the Xenon. This is
due to no out of order execution, less than top notch branch
prediction, and long latencies on floating point operations.
Often times programmers will use a floating point compare to
avoid doing math. In this case its likely to be cheaper to
just do the math than it is to do the test to avoid it.
Floating point branches can sometimes be replaced with vector
branches or floating point selects.

Vector math on Xenon is very fast when the compiler is given
proper room to schedule vector operations. Each vector
pipeline has a set latency, each instruction has an
associated pipeline through which it executes. For example:
vdot3fp always executes in the Vector Dot Pipeline. For more
information about the vector pipelines and latencies refer to
the Xbox 360 SDK Documentation. Each hardware thread has its
\own set of 128 vector registers. The compiler automatically
decides which registers to use based on the code its
compiling, it is very hard to get the compiler to use up all
\of the registers even with a large number of vector
\operations. Most of the functionality of the Xenon vector
pipelines is exposed via the Vector3 and Vector4 classes,
these should always be used instead of the Microsoft
__vector4 structure.

The Xenon does not have any direct pathways between register
sets. This means that any time you want to move data from any
register set to another it has to be saved to memory then
loaded into the destination. When this happens, this triggers
a load-hit store. Once its transferred to the correct
register set, it may also need to be converted to the
appropriate type (ex: integer -\> float). This conversion can
be very slow in some cases.

The largest offenders here are the float/integer conversions
and the float/vector conversions. Float/Integer conversions
need to be evaluated to see if they are really necessary, if
so can they be pipelined better. Float/Vector conversions are
mostly wasteful. Some care must be taken when using vector
functions to keep all of the math in the vector pipeline.
Always use the Vector3 functions that return Vector3s over
the versions that return floats (ex: DotV, MagV, etc). This
may seem wasteful to the average programmer but its actually
far more efficient.

Due to the deep pipelines of the Xenon CPU, it is very common
for the CPU to stall after every instruction. If one
instruction requires the data output from the previous
instruction, the CPU will stall for several cycles until the
data becomes available. This is obviously less than optimal.
This is unavoidable in some cases. Loops are one place where
this does not have to happen however. If you unroll the loop
to do more operations in one pass then you are basically
doing iterations for free since the CPU is not just idle
waiting for data to become available. This is a huge win and
where most of the power on the system comes from.

When unrolling loops you should pad out your data structures
to avoid complicated exit conditions from your loop. For
\example, say you had an array of 30 vectors that needed some
vector operations done on them. Now if you process 8 vectors
at a time, you would have to test on each iteration to make
sure you don't write past the end of the array. This can be
very costly and less than optimal since the compiler wont be
able to schedule around the branches. However, if you were to
pad the array out to 32 vectors then you can let your loop
execute with no extra branches. The memory to performance
trade off here is very large in most cases, you get a lot of
speed for a small amount of memory.

Should a loop be unrolled? How many times should you unroll a
loop?

A loop should be unrolled if it is a performance bottleneck
and if there are data pipeline stalls. You can find data
pipeline stalls by using the pipeline simulator in the
compiler. A loop should be unrolled as many times as needed
for the compiler to generate properly pipelined code. This
can be a bit tricky since the various pipelines have
different depths. For instances, integer operations are very
fast and vector operations are longer. It is very easy to
choke the CPU by feeding to many instructions down one
pipeline. The compiler does not currently do a very good job
with scheduling, you will need to move things around in your
unrolled loop to get the best performance.

Tracedump is one of the most useful performance tools for the
CPU. Tracedump records all of the instructions executed
within a block of code and spits out useful information about
them. Tracedump is very good at locating load-hit stores,
floating point branches, and expensive heavily used
instructions.

The Core subsystem is the heart of RAGE. Every other
subsystem in RAGE depends on Core for its basic data
structures, string output, assertions, file handling, vector/matrix arithmetic, etc. The Core subsystem includes the
following modules:
 - atl: A Template Library (intended to be used instead of
      STL, and contains unique items NOT in STL; we will be
      migrating over to STL over time and deprecating components
      here as appropriate).
 - diag: Assertion support, TTY output, memory usage
      tracking.
 - file: File input and output; token parsing and
      serialization.
 - math: Scalar math, curve fitting, and random number
      generation
 - paging: Support for asychronous loading of baked data
      and construction of resource heaps
 - string: Basic string hashing and unicode support.
 - system: semaphore and thread management, time
      management, low-level timers, command-line parameter
      processing, and startup code.
 - vector: Provides linear-algebra functionality, first
      level of 3-D graphics methods (e.g. intersections, distances,
      resolving collisions, etc.), vector and matrix and quaternion
      classes.
 - zlib: Port of zlib 1.2.1

The non-private components of the Graphics (low level)
subsystem provide texture management, viewports, and the
drawing of geometry ranging from dynamic objects to pre-built
levels. The low-level Graphics subsystem includes the
following modules:
 - grcore: setup and teardown, immediate mode rendering,
      viewports (with sphere culling), fonts, texture management
 - grmodel: shaders and models
	
* Graphics, high level *
The non-private components of the high-level Graphics
subsystem provide particle systems and in-game text
rendering. The high-level Graphics subsystem includes the
following modules:
 - devcam: simple development cameras for viewing scenes
 - rmcore: Drawables, which are complex objects with
      multiple levels of detail, with each level of detail
      consisting of either a single skinned object or one or more
      non-skinned objects all attached to arbitrary bones.

## Audio
The non-private components of the Audio sub-system provide a
low-level, cross-platform API. The Audio sub-system includes the following modules:
 - audiocommand
 - audiocontrol
 - audiodriver
 - sample_audiocontrol
	
## Physics
The non-private components of the Physics subsystem provide
collision detection and response at levels ranging from
individual polygons to whole objects. The Physics subsystem
includes the following modules:
 - crphysics
 - phcore
 - phbound
 - phinertia
 - physics
 - pheffects
 - phtest
	
## Vehicle
The non-private components of the Vehicle subsystem are used
to simulate wheeled vehicles. Vehicle is dependent on
Physics. The Vehicle subsystem includes the following
modules:
 - veh_base
 - veh_car
 - veh_ctrl
 - veh_dyna
 - veh_gfx
 - veh_cam
 - veh_aud
	
## Creature
The Creature subsystem provides all the functions to load
skeleton data from files into game tools; to
locate skeleton with animation data or IK solutions; and to
compute local and global transformation matrices. Creature
has all functions to load animation data from files into game
tools; to generate new animation data with
a blender; to pose the skeleton with the animation data; and
to save the animation data as resources into files.

The Creature subsystem includes the following modules:
 - crskeleton: Skeleton management
 - cranimation: Animation playback

Using RAGE effectively is one of the most important things a project can do to achieve success. However, changes to RAGE can sometimes be disruptive if they are incomplete, buggy, or change an interface that project-specific code depends upon. To minimize these and other problems that haunt shared code, a system using CVS tags has been set up.
To lessen delays from bugs and inefficiencies in shared code, RAGE code is put through a battery of tests on a weekly basis. If the code proves to be stable and free of internal bugs, it is tagged, documented, and released to the company. This release of RAGE code is frozen in time, so it can be retrieved by using the Getage script for each project.
