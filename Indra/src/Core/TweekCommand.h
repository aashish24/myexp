/******************************************************************************
 *
 * Class defines the what defines a tweek command. 
 *
 ******************************************************************************
 */

#ifndef __TWEEK_COMMAND_H__
#define __TWEEK_COMMAND_H__
     
#include "Export.h"

class CORE_EXPORT TweekCommand
{
	public:
		TweekCommand()
		{}

		~TweekCommand()
		{}

		std::string mIdentifier;
		std::string mEntity;
		std::string mStateAttribute;
		std::string mModifierString;
		bool mModifierBoolean;
		long mModifierLong;
};

#endif //  __TWEEK_COMMAND_H__
