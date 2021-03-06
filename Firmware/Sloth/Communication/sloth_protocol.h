/* Adding an offset to enums cause it to start
   with a value that represents an ASCII character,
   so the communication is readable through serial terminal */
#ifndef SLOTH_PROTOCOL_DEF_H
#define SLOTH_PROTOCOL_DEF_H

#define ENUM_OFFSET	0x21 // Adding an offset to enums
#define SLOTH_PROTOCOL_CMD_MAX_SIZE (SLOTH_OPCODE_EOF - ENUM_OFFSET)

typedef enum sloth_opcode
{
	SLOTH_OPCODE_INC = ENUM_OFFSET,
	SLOTH_OPCODE_DEC,
	SLOTH_OPCODE_SET,
	SLOTH_OPCODE_CONFIG,
	SLOTH_OPCODE_START,
	SLOTH_OPCODE_STOP,
	SLOTH_OPCODE_SAVE,
	SLOTH_OPCODE_EOF  //!< Marks the largest value for opcode
}sloth_opcode_t;

// for now, maybe status isn't a big deal
#if 0
typedef enum sloth_op_status
{
	SLOTH_STATUS_SUCCESS = ENUM_OFFSET,
	SLOTH_STATUS_BUSY,
	SLOTH_STATUS_INVALID_PARAM,
	SLOTH_STATUS_ERROR,
	SLOTH_STATUS_EOF
}sloth_op_status_t;
#endif

typedef enum sloth_ctrl_var
{
	SLOTH_VAR_KP = ENUM_OFFSET,
	SLOTH_VAR_KI,
	SLOT_VAR_KD,
	SLOT_VAR_EOF,
}sloth_ctrl_var_t;

typedef struct __attribute__((__packed__)) sloth_config
{
	uint32_t kp;
	uint32_t ki;
	uint32_t kd;
}sloth_config_t;

// todo: define a better name for this.
typedef struct __attribute__((__packed__)) sloth_var_set
{
	sloth_ctrl_var_t var;
	uint32_t value;
}sloth_var_set_t;

/*  Defining a type for the structure of a command. */
typedef struct __attribute__((__packed__)) sloth_cmd
{
	sloth_opcode_t 		cmd;
	// sloth_op_status_t 	status;	// for now, maybe status isn't a big deal
	union
	{
		sloth_var_set_t  variable;
		sloth_config_t	 config;
	};
	// uint16_t crc; // for now we dont need CRC
}sloth_cmd_t;

#endif // SLOTH_PROTOCOL_DEF_H
