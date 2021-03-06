/* -*- C++ -*- */

//=============================================================================
/**
 * @file   modAOS_VC_Frame.hpp
 * @author Tad Kollar  
 *
 * $Id: modAOS_VC_Frame.hpp 1602 2012-06-21 14:42:25Z tkollar $ 
 * Copyright (c) 2010.
 *      NASA Glenn Research Center.  All rights reserved.
 *      See COPYING file that comes with this distribution.
 */
//=============================================================================

#ifndef _MOD_AOS_VC_FRAME_HPP_
#define _MOD_AOS_VC_FRAME_HPP_

#include "AOS_VirtualChannel_Service.hpp"

namespace nAOS_VC_Frame {

//=============================================================================
/**
 * @class modAOS_VC_Frame
 * @author Tad Kollar  
 * @brief Wrap incoming AOS Transfer Frame buffers with AOS_Transfer_Frame objects.
 */
//=============================================================================
class modAOS_VC_Frame: public AOS_VirtualChannel_Service {
public:
	/// Primary constructor.
	/// @param newName An identifier for the module that's unique within the channel.
	/// @param newChannelName An identifier for the containing channel.
	/// @param newDLLPtr Pointer to the DLL management structure.
    modAOS_VC_Frame(const std::string& newName, const std::string& newChannelName,
    	 const CE_DLL* newDLLPtr);

	/// Destructor
    ~modAOS_VC_Frame();

	/// Read in data, verify header, and send it on.
	int svc();
	
	/// Override BaseTrafficHandler::getMRU() with a calculation.
	size_t getMRU() const { return getFrameSize(); }
		
	/// Override BaseTrafficHandler::setMRU() to calculate frameSize_ instead of MRU_.
	/// @param newVal The new data zone length.
	void setMRU(const size_t newVal) { setFrameSize(newVal); }
	
	/// Override BaseTrafficHandler::getMTU() to return _frameSize instead of _MTU.
	size_t getMTU() const { return getFrameSize(); }
	
	/// Override BaseTrafficHandler::setMTU() to set frameSize_ instead of MTU_.
	void setMTU(const size_t newVal) { setFrameSize(newVal); }		
	
	/// Return a pointer to a duplicate of _idleFrameTemplate.
	NetworkData* getIdleUnit();
	
	/// Create a PeriodicLink to manage the existance of the connection from
	/// this handler's output to the next handler's input.
	/// @param target The Traffic Handler to output to.
	/// @param sourceOutputRank Whether to connect the source's primary or auxiliary output.
	/// @param targetInputRank Whether to connect to the target's primary or auxiliary input.
	/// @param postOpen True if the link is being created after the source is already active.
	void connectOutput(BaseTrafficHandler* target,
		const HandlerLink::OutputRank sourceOutputRank = HandlerLink::PrimaryOutput,
		const HandlerLink::InputRank targetInputRank = HandlerLink::PrimaryInput,
		const bool postOpen = false ) {
			connectPeriodicOutput(target, sourceOutputRank, targetInputRank, postOpen);
	}
		
protected:
	
	/// Delete old (if exists), create and configure the idle frame template.
	void rebuildIdleUnitTemplate_();
	
}; // class modAOS_VC_Frame

} // namespace nAOS_VC_Frame

#endif // _MOD_AOS_VC_FRAME_HPP_
