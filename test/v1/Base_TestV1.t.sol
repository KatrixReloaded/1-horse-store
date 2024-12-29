//SPDX-License-Identifier: GPL-3.0-only
pragma solidity 0.8.20;

import { Test, console2 } from "../../lib/forge-std/Test.sol";
import { HorseStore } from "../../src/horseStoreV1/HorseStore.sol";

abstract contract Base_TestV1 is Test {
    HorseStore public horseStore;

    function setUp() public virtual {
        horseStore = new HorseStore();
    }

    function testReadValue() public {
        uint256 initValue = horseStore.readNumberOfHorses();
        assertEq(initValue, 0);
    }
}