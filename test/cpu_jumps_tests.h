#include "gtest/gtest.h"
#include "cpu/cpu.h"

TEST(CPU_JUMP, JumpImmediateValue) {
    // TODO JP nn
}

TEST(CPU_JUMP, JumpImmediateValueNotZeroFlag) {
    // TODO JP cc, nn Not Zero Flag
}

TEST(CPU_JUMP, JumpImmediateValueZeroFlag) {
    // TODO JP cc, nn Zero Flag
}

TEST(CPU_JUMP, JumpImmediateValueNotCarryFlag) {
    // TODO JP cc, nn Not Carry Flag
}

TEST(CPU_JUMP, JumpImmediateValueCarryFlag) {
    // TODO JP cc, nn Carry Flag
}

TEST(CPU_JUMP, JumpHL) {
    // TODO JP (HL)
}

TEST(CPU_JUMP, JumpAdd) {
    // TODO JR e
}

TEST(CPU_JUMP, JumpAddNotZeroFlag) {
    // TODO JR cc, n Not Zero Flag
}

TEST(CPU_JUMP, JumpAddZeroFlag) {
    // TODO JR cc, n Zero Flag
}

TEST(CPU_JUMP, JumpAddNotCarryFlag) {
    // TODO JR cc, n Not Carry Flag
}

TEST(CPU_JUMP, JumpAddCarryFlag) {
    // TODO JR cc, n Carry Flag
}