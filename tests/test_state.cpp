#include <gtest/gtest.h>
#include "state_machine.h"

TEST(StateMachine, Command) {
    StateMachine state_machine(2);
    state_machine.push_command("1");
    state_machine.push_command("2");

    ASSERT_EQ(state_machine.current_state(), STATE::COMMAND);
}

TEST(StateMachine, Block) {
    StateMachine state_machine(2);
    state_machine.push_command("1");
    state_machine.push_command("{");

    ASSERT_EQ(state_machine.current_state(), STATE::BLOCK);
}

TEST(StateMachine, CloseBlock) {
    StateMachine state_machine(1);
    state_machine.push_command("{");
    state_machine.push_command("2");
    state_machine.push_command("}");

    ASSERT_EQ(state_machine.current_state(), STATE::COMMAND);
}


TEST(StateMachine, InnerBlock) {
    StateMachine state_machine(1);
    state_machine.push_command("{");
    state_machine.push_command("2");
    state_machine.push_command("{");
    state_machine.push_command("3");
    state_machine.push_command("}");
    state_machine.push_command("}");

    ASSERT_EQ(state_machine.current_state(), STATE::COMMAND);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
