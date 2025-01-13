// 0x6080604052 348015600e575f80fd5b5060a58061001b5f395ff3fe6080604052348015600e575f80fd5b50600436106030575f3560e01c8063cdfead2e146034578063e026c017146045575b5f80fd5b6043603f3660046059565b5f55565b005b5f5460405190815260200160405180910390f35b5f602082840312156068575f80fd5b503591905056fea2646970667358221220f4cc721dc409b528475d0864e930edfca7075364564549d6a1e547f09bdb547a64736f6c63430008140033

// 3 sections
// 1. Contract Creation
// 2. Runtime
// 3. Metadata

// 1. Contract Creation Code
// Free Memory Pointer
PUSH1 0x80        // [0x80]
PUSH1 0x40        // [0x40, 0x80]
MSTORE            // []

// What does this chunk do?
// Jumps if no value is sent with transaction, else revert
// If we make the contract have a payable constructor, the compiler would then skip this part [L#17-L#24]
CALLVALUE         // [msg.value]
DUP1              // [msg.value, msg.value]
ISZERO            // [msg.value == 0, msg.value]
PUSH1 0x0e        // [0x0e, msg.value == 0, msg.value]
JUMPI             // [msg.value]
PUSH0             // [0x00, msg.value]
DUP1              // [0x00, 0x00, msg.value]
REVERT            // [msg.value]

JUMPDEST          // [msg.value]
POP               // []
PUSH1 0xa5        // [0xa5]
DUP1              // [0xa5, 0xa5]
PUSH2 0x001b      // [0x001b, 0xa5, 0xa5]
PUSH0             // [0x00, 0x001b, 0xa5, 0xa5]
CODECOPY          // [0xa5]                             Memory:[runtime code]
PUSH0             // [0x00, 0xa5]
RETURN            // []
INVALID           // []                                 Contract Creation Code ends here



// 2. Runtime Code
// Entry point of all calls
// Free Memory Pointer
PUSH1 0x80
PUSH1 0x40
MSTORE

// Checking for msg.value, if not 0, revert
CALLVALUE         // [msg.value]
DUP1              // [msg.value, msg.value]
ISZERO            // [msg.value == 0, msg.value]
PUSH1 0x0e        // [0x0e, msg.value == 0, msg.value]
JUMPI             // [msg.value]
// Jump to JUMPDEST on L#57
PUSH0             // [0x00, msg.value]
DUP1              // [0x00, 0x00, msg.value]
REVERT            // [msg.value]

JUMPDEST          // [msg.value]
POP               // []
PUSH1 0x04        // [0x04]
CALLDATASIZE      // [calldata_size, 0x04]
LT                // [calldata_size < 0x04]
PUSH1 0x30        // [0x30, calldata_size < 0x04]
JUMPI             // []
// Jump if calldata_size is less than 4 bytes to revert as there is no function selector in calldata (L#82)

PUSH0             // [0x00]
CALLDATALOAD      // [32-bytes of calldata]
PUSH1 0xe0        // [0xe0, 32-bytes of calldata]       0xe0 (=224) is the offset in bits, which is 28 bytes
SHR               // [calldata[0:4]]                    function_selector      
DUP1              // [function_selector, function_selector]
PUSH4 0xcdfead2e  // [0xcdfead2e, function_selector, function_selector]
EQ                // [function_selector == 0xcdfead2e, function_selector]
PUSH1 0x34        // [0x34, function_selector == 0xcdfead2e, function_selector]
JUMPI             // [function_selector]
DUP1              // [function_selector, function_selector]
PUSH4 0xe026c017  // [0xe026c017, function_selector, function_selector]
EQ                // [function_selector == 0xe026c017, function_selector]
PUSH1 0x45        // [0x45, function_selector == 0xe026c017, function_selector]
JUMPI             // [function_selector]

// Revert JumpDest
JUMPDEST          // []
PUSH0             // [0x00]
DUP1              // [0x00, 0x00]
REVERT            // []

// updateNumberOfHorses(0xcdfead2e) JumpDest 1
JUMPDEST          // [function_selector]
PUSH1 0x43        // [0x43, function_selector]
PUSH1 0x3f        // [0x3f, 0x43, function_selector]
CALLDATASIZE      // [calldata_size, 0x3f, 0x43, function_selector]
PUSH1 0x04        // [0x04, calldata_size, 0x3f, 0x43, function_selector]
PUSH1 0x59        // [0x59, 0x04, calldata_size, 0x3f, 0x43, function_selector]
JUMP              // [0x04, calldata_size, 0x3f, 0x43, function_selector]

// updateNumberOfHorses(0xcdfead2e) JumpDest 4
JUMPDEST          // [calldata - function_selector, 0x43, function_selector]
PUSH0             // [0x00, calldata - function_selector, 0x43, function_selector]
SSTORE            // [0x43, function_selector]
JUMP              // [function_selector]
// Jump to JumpDest 5

// updateNumberOfHorses(0xcdfead2e) JumpDest 5
JUMPDEST
STOP

// readNumberOfHorses(0xe026c017) JumpDest
// the only jumpdest
JUMPDEST          // [function_selector]
PUSH0             // [0x00, function_selector]
SLOAD             // [numHorses, function_selector]
PUSH1 0x40        // [0x40, numHorses, function_selector]
MLOAD             // [free_memory_pointer = 0x80, numHorses, function_selector]
SWAP1             // [numHorses, 0x80, function_selector]
DUP2              // [0x80, numHorses, 0x80, function_selector]
MSTORE            // [0x80, function_selector]          Memory:[0x80: numHorses]
PUSH1 0x20        // [0x20, 0x80, function_selector]
ADD               // [0xa0, function_selector]
PUSH1 0x40        // [0x40, 0xa0, function_selector]
MLOAD             // [0x80, 0xa0, function_selector]
DUP1              // [0x80, 0x80, 0xa0, function_selector]
SWAP2             // [0xa0, 0x80, 0x80, function_selector]
SUB               // [0xa0 - 0x80, 0x80, function_selector]
SWAP1             // [0x80, 0x20, function_selector]
// Return a value of 0x20 size (32-bytes) that is at location 0x80 in memory
RETURN            // [function_selector]

// updateNumberOfHorses(0xcdfead2e) JumpDest 2
// check to see if there is a value to update the horse number, else revert
JUMPDEST          // [0x04, calldata_size, 0x3f, 0x43, function_selector]
PUSH0             // [0x00, 0x04, calldata_size, 0x3f, 0x43, function_selector]
PUSH1 0x20        // [0x20, 0x00, 0x04, calldata_size, 0x3f, 0x43, function_selector]
DUP3              // [0x04, 0x20, 0x00, 0x04, calldata_size, 0x3f, 0x43, function_selector]
DUP5              // [calldata_size, 0x04, 0x20, 0x00, 0x04, calldata_size, 0x3f, 0x43, function_selector]
SUB               // [calldata_size - 0x04, 0x20, 0x00, 0x04, calldata_size, 0x3f, 0x43, function_selector]
SLT               // [calldata_size - 0x04 < 0x20, 0x00, 0x04, calldata_size, 0x3f, 0x43, function_selector]
ISZERO            // [more_calldata_than_selector?, 0x00, 0x04, calldata_size, 0x3f, 0x43, function_selector]
PUSH1 0x68        // [0x68, more_calldata_than_selector?, 0x00, 0x04, calldata_size, 0x3f, 0x43, function_selector]
JUMPI             // [0x00, 0x04, calldata_size, 0x3f, 0x43, function_selector]
// We are going to jump to jumpdest 3 if there is more calldata than:
// function_selector + 0x20

// Revert if there isn't enough calldata!
PUSH0             // [0x00, 0x00, 0x04, calldata_size, 0x3f, 0x43, function_selector]
DUP1              // [0x00, 0x00, 0x00, 0x04, calldata_size, 0x3f, 0x43, function_selector]
REVERT            // []

// updateNumberOfHorses(0xcdfead2e) JumpDest 3
JUMPDEST          // [0x00, 0x04, calldata_size, 0x3f, 0x43, function_selector]
POP               // [0x04, calldata_size, 0x3f, 0x43, function_selector]
// Ignore the func selector as offset of 4 bytes
CALLDATALOAD      // [calldata - function_selector, calldata_size, 0x3f, 0x43, function_selector]
SWAP2             // [0x3f, calldata_size, calldata - function_selector, 0x43, function_selector]
SWAP1             // [calldata_size, 0x3f, calldata - function_selector, 0x43, function_selector]
POP               // [0x3f, calldata - function_selector, 0x43, function_selector]
JUMP              // [calldata - function_selector, 0x43, function_selector]
// Jump to JumpDest 4

INVALID
LOG2
PUSH5 0x6970667358
INVALID
SLT
KECCAK256
DELEGATECALL
INVALID
PUSH19 0x1dc409b528475d0864e930edfca70753645645
BLOBHASH
INVALID
LOG1
INVALID
SELFBALANCE
CREATE
SWAP12
INVALID
SLOAD
PUSH27 0x64736f6c63430008140033