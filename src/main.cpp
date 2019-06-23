#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "lib/logger.h"
#include "lib/console_handler.h"
#include "server/server.h"
#include "bulk_handler.h"


int main(int argc, char* argv[]) {
    if (argc != 3) {
      std::cerr << "Usage: bulk_server <port> <bulk_size>" << std::endl;
      return 1;
    }
    
    Logger::get().add_handler<ConsoleHandler>();
    try {
        int bulk = std::atoi(argv[2]);
        boost::asio::io_service ios;
        Server s(ios, std::atoi(argv[1]));
        s.start_accept<BulkProtocol, int>(bulk);
        ios.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

  return 0;
}
