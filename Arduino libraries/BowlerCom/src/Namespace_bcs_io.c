/**
 * @file Namespace_bcs_io.c
 *
 * Created on: Mar 16, 2013
 * @author hephaestus
 */

#include <BowlerCom.h>
//char ioNSName[] = "bcs.io.*;0.3;;";

boolean noAsyncMode = false;

RunEveryData asyncPulse = {0,100};

void setNoAsyncMode(boolean m) {
	noAsyncMode = m;
}

boolean bcsIoAsyncEventCallback(BowlerPacket *Packet,
		boolean (*pidAsyncCallbackPtr)(BowlerPacket *)) {

	int i;
	boolean update = false;
	if(RunEvery(&asyncPulse)>0){
		for (i = 0; i < GetNumberOfIOChannels(); i++) {
			//
			if (pushAsyncReady(i)) {
	//        	println_W("Pin Async ");p_int_W(i);
	//        	print_W(" val= ");p_int_W(GetChanelSingleValue(i));
	//        	print_W(" type = ");printAsyncType(i,WARN_PRINT);
	//        	print_W(" mode = ");printMode(i,GetChannelMode(i),WARN_PRINT);
				update = true;
			}
		}
	}
	if (noAsyncMode == true) {
		return false;
	}
	if (update) {
		GetAllChanelValueFromPacket(Packet);
		Packet->use.head.DataLegnth = 4 + 1 + GetNumberOfIOChannels() * 4;
		Packet->use.head.Method = BOWLER_ASYN;
		FixPacket(Packet);

		//println_W("bcsIoAsync ");printPacket(Packet, WARN_PRINT);

		if (pidAsyncCallbackPtr != NULL) {
			pidAsyncCallbackPtr(Packet);
		}
	}
	//println_I("Done bcs.io");
	return false;
}

// GET structures

RPC_LIST bcsIo_gchm_g = { BOWLER_GET, // Method
		"gchm", //RPC as string
		&GetChannelModeFromPacket, //function pointer to a packet parsing function
		{
		BOWLER_I08, // channel
				0 }, // Calling arguments
		BOWLER_POST, // response method
		{
		BOWLER_I08, // channel
				BOWLER_I08, // mode
				0 }, // Calling arguments
		NULL //Termination
		};

RPC_LIST bcsIo_gacm_g = { BOWLER_GET, // Method
		"gacm", //RPC as string
		&GetAllChannelModeFromPacket, //function pointer to a packet parsing function
		{ 0 }, // Calling arguments
		BOWLER_POST, // response method
		{ BOWLER_STR, // all of the channel modes
				0 }, // Calling arguments
		NULL //Termination
		};

RPC_LIST bcsIo_gchv_g = { BOWLER_GET, // Method
		"gchv", //RPC as string
		&GetChanelValueFromPacket, //function pointer to a packet parsing function
		{ BOWLER_I08, // channel
				0 }, // Calling arguments
		BOWLER_POST, // response method
		{ BOWLER_I08, // channel
				BOWLER_I32, // value
				0 }, // Calling arguments
		NULL //Termination
		};

RPC_LIST bcsIo_gacv_g = { BOWLER_GET, // Method
		"gacv", //RPC as string
		&GetAllChanelValueFromPacket, //function pointer to a packet parsing function
		{ 0 }, // Calling arguments
		BOWLER_POST, // response method
		{ BOWLER_I32STR, 0 }, // Calling arguments
		NULL //Termination
		};

RPC_LIST bcsIo_asyn_g = { BOWLER_GET, // Method
		"asyn", //RPC as string
		&GetAsyncFromPacket, //function pointer to a packet parsing function
		{ BOWLER_I08, // channel
				0 }, // Calling arguments
		BOWLER_POST, // response method
		{ BOWLER_I08, // channel
				BOWLER_I08, // Async mode for given channel
				0 }, // Calling arguments
		NULL //Termination
		};

RPC_LIST bcsIo_gchc_g = { BOWLER_GET, // Method
		"gchc", //RPC as string
		&GetIOChannelCountFromPacket, //function pointer to a packet parsing function
		{ 0 }, // Calling arguments
		BOWLER_POST, // response method
		{ BOWLER_I32, 0 }, // Calling arguments
		NULL //Termination
		};

RPC_LIST bcsIo_gcml_g = { BOWLER_GET, // Method
		"gcml", //RPC as string
		&getFunctionList, //function pointer to a packet parsing function
		{ BOWLER_I08, // channel
				0 }, // Calling arguments
		BOWLER_POST, // response method
		{ BOWLER_STR, 0 }, // Calling arguments
		NULL //Termination
		};
//POST

RPC_LIST bcsIo_strm_g = { BOWLER_GET, // Method
		"strm", //RPC as string
		&GetChanelStreamFromPacket, //function pointer to a packet parsing function
		{ BOWLER_I08, // channel
				0 }, // Calling arguments
		BOWLER_POST, // response method
		{ BOWLER_I08, // channel
				BOWLER_STR, // value
				0 }, // Calling arguments
		NULL //Termination
		};

RPC_LIST bcsIo_strm_p = { BOWLER_POST, // Method
		"strm", //RPC as string
		&SetChanelStreamFromPacket, //function pointer to a packet parsing function
		{ BOWLER_I08, // channel
				BOWLER_STR, // value
				0 }, // Calling arguments
		BOWLER_POST, // response method
		{ BOWLER_I08, // code
				BOWLER_I08, // trace
				0 }, // Calling arguments
		NULL //Termination
		};

RPC_LIST bcsIo_schv_p = { BOWLER_POST, // Method
		"schv", //RPC as string
		&SetChanelValueFromPacket, //function pointer to a packet parsing function
		{ BOWLER_I08, // channel
				BOWLER_I32, // value
				BOWLER_I32, // time in ms
				0 }, // Calling arguments
		BOWLER_POST, // response method
		{ BOWLER_I08, // code
				BOWLER_I08, // trace
				0 }, // Calling arguments
		NULL //Termination
		};

RPC_LIST bcsIo_sacv_p = { BOWLER_POST, // Method
		"sacv", //RPC as string
		&SetAllChannelValueFromPacket, //function pointer to a packet parsing function
		{ BOWLER_I32, // time in ms
				BOWLER_I32STR, 0 }, // Calling arguments
		BOWLER_POST, // response method
		{ BOWLER_I32STR, 0 }, // Calling arguments
		NULL //Termination
		};

//
//RPC_LIST bcsIo_asyn_p = {BOWLER_POST, // Method
//    "asyn", //RPC as string
//    &SetAsyncFromPacket, //function pointer to a packet parsing function
//    {BOWLER_I08, // channel
//        BOWLER_I08, // async mode
//        0
//    }, // Calling arguments
//    BOWLER_POST, // response method
//    {0}, // Calling arguments
//    NULL //Termination
//};

//CRIT
RPC_LIST bcsIo_cchn_c = { BOWLER_CRIT, // Method
		"cchn", //RPC as string
		&ConfigureChannelFromPacket, //function pointer to a packet parsing function
		{ BOWLER_I08, // channel to push, Invalad treats it as bulk packet
				BOWLER_BOOL, // change the values
				BOWLER_I32STR, // values
				0 }, // Calling arguments
		BOWLER_POST, // response method
		{ BOWLER_I32STR, // values
		},// Calling arguments
		NULL //Termination
		};

//@Depricated Set Channel value should be replaced with the set all and the stream mode
RPC_LIST bcsIo_schv_c = { BOWLER_CRIT, // Method
		"schv", //RPC as string

		&SetChanelValueFromPacket, //function pointer to a packet parsing function
		{ BOWLER_I08, // channel
				BOWLER_I32STR, // values
				0 }, // Calling arguments
		BOWLER_POST, // response method
		{ 0 }, // Calling arguments
		NULL //Termination
		};

RPC_LIST bcsIo_asyn_c = { BOWLER_CRIT, // Method
		"asyn", //RPC as string
		&configAdvancedAsync, //function pointer to a packet parsing function
		{
		BOWLER_I08, // channel
				BOWLER_I08, // type
				BOWLER_I32, // time in ms
				BOWLER_I32, // compare value
				BOWLER_I08, // threshhold direction
				0 }, // Calling arguments
		BOWLER_POST, // response method
		{ 0 }, // Calling arguments
		NULL //Termination
		};

//Namespace
NAMESPACE_LIST bcsIo = { "bcs.io.*;0.3;;", // The string defining the namespace
		NULL, // the first element in the RPC list
		&bcsIoAsyncEventCallback, // async for this namespace
		NULL // no initial elements to the other namesapce field.
		};

boolean bcsIonamespcaedAdded = false;

NAMESPACE_LIST * get_bcsIoNamespace() {
	if (bcsIonamespcaedAdded != true) {
		bcsIonamespcaedAdded = true;
		//Add the RPC structs to the namespace
		//GET
		addRpcToNamespace(&bcsIo, &bcsIo_gchm_g);
		addRpcToNamespace(&bcsIo, &bcsIo_gacm_g);
		addRpcToNamespace(&bcsIo, &bcsIo_gchv_g);
		addRpcToNamespace(&bcsIo, &bcsIo_gacv_g);
		addRpcToNamespace(&bcsIo, &bcsIo_asyn_g);
		addRpcToNamespace(&bcsIo, &bcsIo_gchc_g);
		addRpcToNamespace(&bcsIo, &bcsIo_gcml_g);
		addRpcToNamespace(&bcsIo, &bcsIo_strm_g);
		//POST
		addRpcToNamespace(&bcsIo, &bcsIo_strm_p);
		addRpcToNamespace(&bcsIo, &bcsIo_schv_p);
		addRpcToNamespace(&bcsIo, &bcsIo_sacv_p);
		//addRpcToNamespace(&bcsIo, & bcsIo_asyn_p);
		//CRIT
		addRpcToNamespace(&bcsIo, &bcsIo_cchn_c);
		addRpcToNamespace(&bcsIo, &bcsIo_schv_c);
		addRpcToNamespace(&bcsIo, &bcsIo_asyn_c);

	}

	return &bcsIo; //Return pointer to the struct
}

