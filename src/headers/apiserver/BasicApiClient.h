/*
 * Copyright (c) 2014, webvariants GmbH, http://www.webvariants.de
 *
 * This file is released under the terms of the MIT license. You can find the
 * complete text in the attached LICENSE file or online at:
 *
 * http://www.opensource.org/licenses/mit-license.php
 * 
 * @author: Tino Rusch (tino.rusch@webvariants.de)
 */

#ifndef __BASICAPICLIENT__
#define __BASICAPICLIENT__

#include "apiserver/JSONTCPClient.h"
#include "events/Manager.h"
#include "util/Any.h"

namespace Susi {
namespace Api {

	class BasicApiClient : protected JSONTCPClient {
	protected:
		
		virtual void onMessage(Susi::Util::Any & message) override;

		Susi::Util::Any eventToAny(Susi::Events::Event & event);
		void anyToEvent(Susi::Util::Any & any, Susi::Events::Event & event);

	public:
		BasicApiClient(std::string addr) : JSONTCPClient{addr} {}
		virtual ~BasicApiClient(){}

		void close(){
			JSONTCPClient::close();
		}

		virtual void onConsumerEvent(Susi::Events::SharedEventPtr event) = 0;
		virtual void onProcessorEvent(Susi::Events::EventPtr event) = 0;
		virtual void onAck(Susi::Events::SharedEventPtr event) = 0;

		void sendPublish(Susi::Events::Event & event);
		void sendRegisterConsumer(std::string topic);
		void sendRegisterProcessor(std::string topic);
		void sendAck(Susi::Events::Event & event);

	};

}
}

#endif // __BASICAPICLIENT__