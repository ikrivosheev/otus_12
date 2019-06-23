#include "handler.h"


class BulkHandler: public IHandler {
    public:
        BulkHandler(int bulk): _bulk(bulk) {}

    private:
        int _bulk;
};
