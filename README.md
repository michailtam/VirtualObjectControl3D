# Virtual Object Control in 3D - MSc thesis

### Description
Unfortunately, there are many people who, due to their physical limitations, are not able to interact with the computer in the same way as other people can. Especially people who have a handicap with their hands and arms can hardly or not at all move a mouse or type on a keyboard. Therefore, special methods must be developed that do not prevent such a group of people from interacting with the computer. Among other things, there are programs that use the voice to perform various operations. Such programs can, for example, write documents and create notes only with speech. But how can people interact with the computer who have both a hand and a speech handicap? Are they not allowed to interact with the computer? Of course not, and that's exactly the purpose of the software which was developed in this project. Using this application, severely disabled people can move around in virtual environments without even using their voice or hands. This enables them to play for example computer games or to move around in virtual worlds or buildings such as virtual museums. But how is this possible? The interaction takes place with certain movements of the head, which are recorded by a 3D camera from Intel and converted into the virtual world.

The software was developed under Windows using the programming language C ++ and the graphics libraries OpenGL and Qt from Trolltech. The virtual world was created with the help of OpenGL and for the graphical user interface (GUI) Qt was used. The purpose of the UI, among other things, is to log the camera properties. If the 3D camera is not connected or if it is faulty, an error message will be displayed. Furthermore, the graphical user interface is used to log the respective camera properties and the head movements the user performs to interact with the virtual world. With the help of this information, both the user and the supervisor can follow which operations are carried out in the virtual world based on the respective head movement.

The purpose of this software is to give suggestions on how to use certain technologies and computer science to help certain groups of people to integrate themselves into the work on the computer.

<h2><b>Programming language, Used Libraries and Components</b></h2>
<table>
	<tr>
		<td>Development Environment</td>
		<td>[Visual Studio](https://visualstudio.microsoft.com/vs/community/), [Qt Creator](https://www.qt.io/download">Qt 
		Creator)</td>
	</tr>
	<tr>
		<td>Programming language</td>
		<td>C++</td>
	</tr>
	<tr>
		<td>Graphics libraries</td>
		<td>[OpenGL](https://www.opengl.org/), [Qt](https://www.qt.io/developers)</td>
	</tr>
	<tr>
		<td>Interaction library</td>
		<td>[Intel® RealSense](https://www.intelrealsense.com/developers)</td>
	</tr>
	<tr>
		<td>3D Camera</td>
		<td>[Intel RealSense F200](https://downloadcenter.intel.com/product/92255/Intel-RealSense-Camera-F200)</td>
	</tr>
</table>

<table align="center">
	<tr>
		<th>Loook Up operation</th>
	</tr>
	<tr>
		<td><img src="https://github.com/michailtam/VirtualObjectControl3D/blob/master/images/look_up.JPG" width=720></td>
	</tr>
	<tr>
		<th>Yaw to the right operation</th>
	</tr>	
	<tr>
		<td><img src="https://github.com/michailtam/VirtualObjectControl3D/blob/master/images/yaw_right.JPG" width=720></td>
	</tr>
	<tr>
		<th>Move forwards operation</th>
	</tr>	
	<tr>
		<td><img src="https://github.com/michailtam/VirtualObjectControl3D/blob/master/images/move_forwards.JPG" width=720></td>
	</tr>
	<tr>
		<th>Intel RealSense 3D camera F200</th>
	</tr>	
	<tr>
		<td><img src="https://github.com/michailtam/VirtualObjectControl3D/blob/master/images/camera_prop.JPG" width=400></td>
	</tr>
</table>
