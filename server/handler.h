#ifndef HANDLER_H
#define HANDLER_H


class IHandler {
    public:
        void connection_made();
        void data_received(char*, std::size_t);
        void connection_lost();
};


#endif // HANDLER_H
