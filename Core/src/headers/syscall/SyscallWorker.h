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

#ifndef __SYS_CALL_WORKER__
#define __SYS_CALL_WORKER__

#include "util/Any.h"
#include <fstream>
#include <iostream>

namespace Susi {
    namespace Syscall {
        class Worker {
        protected:
            Susi::Events::EventPtr _event;
            std::string _command;
            std::vector<std::string> _args;

            std::string getContentFromStream( std::istream& stream ) {
                std::string result {""};
                while( stream.good() ) {
                    char buff[1024];
                    stream.getline( buff,1024 );
                    result += std::string {buff};
                }
                return result;
            }

        public:
            Worker( Susi::Events::EventPtr event, std::string command, std::vector<std::string> args ) :
                _event {std::move( event )},
                   _command {command},
            _args {args} {}

            Worker( Worker & other ) :
                _event {std::move( other._event )},
                   _command {other._command},
            _args {other._args} {}

            Worker( Worker && other ) :
                _event {std::move( other._event )},
                   _command {std::move( other._command )},
            _args {std::move( other._args )} {}

            void operator()() {
                std::string command = _command+" ";
                for(auto arg : _args){
                    command += arg+" ";
                }
                FILE *in;
                char buff[512];
                if(!(in = popen(command.c_str(), "r"))){
                    _event->payload["return"] = 1;
                    return;
                }
                std::string output = "";
                while(fgets(buff, sizeof(buff), in)!=NULL){
                    output += std::string{buff};
                }
                int ret = pclose(in);
                int returnCode = WEXITSTATUS(ret);
                _event->payload["return"] = returnCode;
                _event->payload["stdout"] = output;
                _event->payload["stderr"] = "";
                // when event gets destructed, its acknowledged.
            }
        };
    }
}

#endif // __SYS_CALL_WORKER__