## Animations:

The skeleton data is exported from Maya into R* game format (.skel files)
It was generated originally in Maya and exported into the game format. The skeleton can posed with animations and/or IK.

The RAGE Animation library has all functions: 
 - to load animation data from files into game tools (PS2, XB, GC, PC),
 - to generate new animation data with blender,
 - to pose the skeleton with the animation data,
 - to save the animation data as resources into files.

There may be many animations for one character. The animation data has to have the same number of channels and bones as the skeleton in order for the animation to play back correctly.
crAnimation has enough information to check if it can be applied to the skeleton.
The compression method used for the animation channels is to store the minimum and maximum
range of the channel as floats and used a fixed point 16 bit interpolant for each channel frame.
If the channel does not change during the animation, then no interpolants are stored.

## The RAGE creature library contains the following components:
 - **crBone**: `Defines the skeletal bone. It contains rotation and translation data to locate the bone in the skeletal chain (or skeleton). It also has functions to compute local and global transformation matrices.`

 - **crBoneData**: `Contains extra bone data, such as the number of DOFs, bone limits, and bone index. The bone transformation is computed in crBone.`

 - **crSkeleton**: `Defines the skeletal chain. A skeleton contains a list of crBone objects. The skeleton data is stored in the data member crSkeletonData.`

 - **crSkeletonData**: `Contains skeleton data, such as total translation and rotation DOFs, the number of bones, and a list of bone data. The data can be loaded from a file and written into a file.`

 - **crArmData**: `Defines the arm branch of the skeleton. The arm contains bones like spine, clavicle, shoulder, elbow, and wrist, all instances of crBoneData. With a given IK goal, the IK solution can be solved for the arm.`

 - **crHeadData**: `Defines the head branch of the skeleton. The head contains bones like spine, neck, and head, all instances of crBoneData. With a given IK goal, the IK solution can be solved for the head.`

 - **crLegData**: `Defines the leg branch of the skeleton. The leg contains bones like pelvis, hip, knee, ankle, and toe, all instances of crBoneData. With a given IK goal, the IK solution can be solved for the leg.`

 - **crSpineData**: `Defines the spine branch of the skeleton. The spine contains bones (starting from the root) like several spines and pelvis, all instances of crBoneData. With a given IK goal, the IK solution can be solved for the spine.`

 - **crBodyDataBase**: `Defines the minimal interface for body data.`

 - **crBodyData**: `Derived from crBodyDataBase, it defines the complete skeleton for a character. The body contains branches like spine, head, arms, and legs. A valid body means that all branches are valid. The IK can be solved through each branch of the body.`

 - **crIKGoal**: `Defines the IK goal. An IK goal has two components, translation goal, and rotation goal. The IK solution can be blended with the original bone data locally.`

 - **crKinematicsBase**: `Contains all the necessary components for the inverse kinematics system.`

 - **crKinematics**: `Derived from crKinematicsBase, it defines the center of the inverse kinematics system.
In this center, there are body data initialized with the skeleton data and IK goals for different branches of the skeleton. When the center updates, it triggers the IK process to solve the IK solutions for branches.`

## The RAGE animation library contains the following components:
 - **crAnimation**: `Contains a list of frame data, either normal data or compressed ones. The crAnimation object does not know where its frame data may be applied.`

 - **crAnimBlender**: `Has a list of animations (represented by crAnimPlayer). During playback, it blends all animations linearly and applies the blending result to the skeleton.
It can also blend all its animations with an input animation. The crAnimBlender object may know which skeleton it is going to apply the blending result.`

 - **crAnimPlayer**: `Contains data for animation controls, such as blend-in, blend-out, rate, loop, pause.
The real animation data could be from a crAnimation object, crAnimFrame object, or another crAnimBlender object.`

 - **crAnimFrame**: `The base of this library, as the basic functionalities are done in this class, such as blending frame data, posing the skeleton, and other manipulations of the animation data.`

 - **crAnimCompressor**: `The base class for compressed animation data.`
