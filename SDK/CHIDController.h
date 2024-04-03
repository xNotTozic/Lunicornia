#pragma once

class C_HIDController { // Updated
private:
	char pad_0x0000[0x50]; //0x0000 // Updated
public:
	union {
		struct {
			bool leftClickDown; //0x0050  // Updated
			bool rightClickDown; //0x0051  // Updated
			bool wheelDown; //0x0052  // Updated
			bool mouse4Down; //0x0053 // Updated
			bool mouse5Down; //0x0054 // Updated
		};
		bool clickMap[5]; // Updated
	};
	
};