/*
 * Copyright (c) 2014, webvariants GmbH, http://www.webvariants.de
 *
 * This file is released under the terms of the MIT license. You can find the
 * complete text in the attached LICENSE file or online at:
 *
 * http://www.opensource.org/licenses/mit-license.php
 * 
 * @author: Thomas Krause (thomas.krause@webvariants.de)
 */

#ifndef __HTTP_CLIENT__
#define __HTTP_CLIENT__

#include <iostream>
#include <string>

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTMLForm.h>

#include <Poco/StreamCopier.h>

#include <Poco/URI.h>

#include <Poco/Path.h>

#include <Poco/Exception.h>

#include <Poco/StreamCopier.h>

namespace Susi {
	class HttpClient {
		protected:
			std::string _uri;
		public:
			HttpClient(std::string uri);

			std::string get(std::string req);
			std::string post(std::string req);
			
			void connectWebSocket(std::string socket);
			void send(std::string data);
			std::string recv();			
	};
}

#endif // __HTTP_CLIENT__