# Virtual Object Control in 3D - BSc thesis

### Description
Unfortunately, there are many people who, due to their physical limitations, are not able to interact with the computer in the same way as other people can. Especially people who have a handicap with their hands and arms can hardly or not at all move a mouse or type on a keyboard. Therefore, special methods must be developed that do not prevent such a group of people from interacting with the computer. Among other things, there are programs that use the voice to perform various operations. Such programs can, for example, write documents and create notes only with speech. But how can people interact with the computer who have both a hand and a speech handicap? Are they not allowed to interact with the computer? Of course not, and that's exactly the purpose of the software which was developed in this project. Using this application, severely disabled people can move around in virtual environments without even using their voice or hands. This enables them to play for example computer games or to move around in virtual worlds or buildings such as virtual museums. But how is this possible? The interaction takes place with certain movements of the head, which are recorded by a 3D camera from Intel and converted into the virtual world.

### Prerequisites
To understand in detail how the application works and how the modules (i.e. classes) operate together, the reader must be familiar in low-level computer graphics, computer vision and image processing. He also must have solid programming experience in developing software using C++ (especially modern C++). 

### Development
The software was developed in an OOP approach under Windows using the programming language C++ and the graphics libraries [OpenGL](https://www.opengl.org/), [GLSL](https://www.khronos.org/opengl/wiki/OpenGL_Shading_Language) and [Qt](https://www.qt.io/developers) from Trolltech. The virtual world was created with the help of OpenGL and for the graphical user interface (GUI) Qt was used. The purpose of the UI, among other things, is to log the camera properties. If the 3D camera is not connected or if it is faulty, an error message will be displayed. Furthermore, the graphical user interface is used to log the respective camera properties and the head movements the user performs to interact with the virtual world. With the help of this information, both the user and the supervisor can follow which operations are carried out in the virtual world based on the respective head movement. The [Intel® RealSense SDK](https://www.intelrealsense.com/developers) also provides algorithms for facial expressions detection, face recognition, hand gestures etc.

<table>
	<tr>
		<td>DEV environments</td>
		<td><a href="https://visualstudio.microsoft.com/vs/community/">Visual Studio</a>, <a href="https://www.qt.io/download">Qt Creator</a> 
		</td>
	</tr>
	<tr>
		<td>Programming language</td>
		<td>C++11</td>
	</tr>
	<tr>
		<td>Graphics libraries</td>
		<td><a href="https://www.opengl.org/">OpenGL</a>, <a href="https://www.qt.io/developers">Qt</a></td>
	</tr>
	<tr>
		<td>Shading language</td>
		<td><a href="https://www.khronos.org/opengl/wiki/OpenGL_Shading_Language">GLSL 4.3</a></td>
	</tr>
	<tr>
		<td>Interaction library</td>
		<td><a href="https://www.intelrealsense.com/developers">Intel® RealSense SDK</a></td>
	</tr>
	<tr>
		<td>3D Camera</td>
		<td><a href="https://downloadcenter.intel.com/product/92255/Intel-RealSense-Camera-F200">Intel RealSense F200</a></td>
	</tr>
</table>

### Features
- A 3D camera is used to record the image frames of the movements
- Only head movements can be performed and logged (The SDK provides also)
- GUI provided which serves for help in orientation 
- Head movements can be logged
- Head movements can be observed based on the orientation of the objects in the virtual world
- If the camera is not connected an error message gets displayed

### Main modules
In the following the main modules (classes) are depicted which are the most important part of the project. The shown class diagrams show how all classes are interconnected to each other.
<table>
	<th>
		<td>Module</td>
		<td>Diagram</td>
	</th>
	<tr>
		<td>Intel RealSense Module</td>
		<td><img src="https://github.com/michailtam/VirtualObjectControl3D/blob/master/images/intelrs_module.png" width=720></td>
	</tr>
	<tr>
		<td>Window embeddings</td>
		<td><img src="https://github.com/michailtam/VirtualObjectControl3D/blob/master/images/all_windows.png" width=720></td>
	</tr>
	<tr>
		<td>Window embeddings</td>
		<td><img src="https://github.com/michailtam/VirtualObjectControl3D/blob/master/images/irs_opengl.png" width=720></td>
	</tr>
</table>

### Purpose
The purpose of this software is to provide inspiration for developers and reasearchers on how to use certain technologies and computer science to help certain groups of people to integrate themselves into the work on the computer.

### Screenshots
<table align="center">
	<tr>
		<th>Looking up</th>
	</tr>
	<tr>
		<td><img src="https://github.com/michailtam/VirtualObjectControl3D/blob/master/images/look_up.jpg" width=720></td>
	</tr>
	<tr>
		<th>Yaw to the right</th>
	</tr>	
	<tr>
		<td><img src="https://github.com/michailtam/VirtualObjectControl3D/blob/master/images/yaw_right.jpg" width=720></td>
	</tr>
	<tr>
		<th>Move head forwards</th>
	</tr>	
	<tr>
		<td><img src="https://github.com/michailtam/VirtualObjectControl3D/blob/master/images/move_forwards.jpg" width=720></td>
	</tr>
	<tr>
		<th>Intel RealSense 3D camera F200</th>
	</tr>	
	<tr>
		<td><img src="https://github.com/michailtam/VirtualObjectControl3D/blob/master/images/camera_prop.jpg" width=400></td>
	</tr>
</table>
