#ifndef _ADAPTOR_H
#define _ADAPTOR_H

typedef int (*sc_adaptor_start_transmit_fn_t)(void *adaptor);
typedef int (*sc_adaptor_stop_transmit_fn_t)(void *adaptor);

typedef int (*sc_adaptor_write_data_fn_t)(void *adaptor, int data);
typedef int (*sc_adaptor_write_init_fn_t)(void *adaptor, int data);

typedef int (*sc_adaptor_write_byte_fn_t)(void *adaptor, int data);

struct sc_adaptor_i {
	sc_adaptor_start_transmit_fn_t start_transmit;
	sc_adaptor_stop_transmit_fn_t stop_transmit;
	sc_adaptor_write_data_fn_t write_data;
	sc_adaptor_write_init_fn_t write_init;
};

int sc_adaptor_write_init_and_args(struct sc_adaptor_i **self, int init, int arg_cnt, ...);

static inline int sc_adaptor_start_transmit(void *self)
{
	return (*(struct sc_adaptor_i **)self)->start_transmit(self);
}

static inline int sc_adaptor_stop_transmit(void *self)
{
	return (*(struct sc_adaptor_i **)self)->stop_transmit(self);
}

static inline int sc_adaptor_write_data(void *self, int data)
{
	return (*(struct sc_adaptor_i **)self)->write_data(self, data);
}

static inline int sc_adaptor_write_init(void *self, int data)
{
	return (*(struct sc_adaptor_i **)self)->write_init(self, data);
}

/// The controlling logic of I2C adaptors is different.
struct sc_byte_adaptor_i {
	sc_adaptor_start_transmit_fn_t start_transmit;
	sc_adaptor_stop_transmit_fn_t stop_transmit;
	sc_adaptor_write_byte_fn_t write_byte;
};

static inline int sc_adaptor_i2c_start_transmit(void *self)
{
	return (*(struct sc_byte_adaptor_i **)self)->start_transmit(self);
}

static inline int sc_adaptor_i2c_stop_transmit(void *self)
{
	return (*(struct sc_byte_adaptor_i **)self)->stop_transmit(self);
}

static inline int sc_adaptor_i2c_write_byte(void *self, int data)
{
	return (*(struct sc_byte_adaptor_i **)self)->write_byte(self, data);
}

#endif
