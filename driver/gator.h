/**
 * Copyright 2010  ARM, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef GATOR_H_
#define GATOR_H_

#include <linux/version.h>
#include <linux/fs.h>
#include <linux/mm.h>

/******************************************************************************
 * Filesystem
 ******************************************************************************/
int gatorfs_create_file_perm(struct super_block *sb, struct dentry *root,
	char const *name, const struct file_operations *fops, int perm);

struct dentry *gatorfs_mkdir(struct super_block *sb,
	struct dentry *root, char const *name);

int gatorfs_create_ulong(struct super_block *sb, struct dentry *root,
	char const *name, unsigned long *val);

int gatorfs_create_ro_ulong(struct super_block *sb, struct dentry *root,
	char const *name, unsigned long *val);

/******************************************************************************
 * Tracepoints
 ******************************************************************************/
#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 32)
#	error Kernels prior to 2.6.32 not supported
#elif LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 35)
#	define GATOR_DEFINE_PROBE(probe_name, proto) \
		static void probe_##probe_name(PARAMS(proto))
#	define GATOR_REGISTER_TRACE(probe_name) \
		register_trace_##probe_name(probe_##probe_name)
#	define GATOR_UNREGISTER_TRACE(probe_name) \
		unregister_trace_##probe_name(probe_##probe_name)
#else
#	define GATOR_DEFINE_PROBE(probe_name, proto) \
		static void probe_##probe_name(void *data, PARAMS(proto))
#	define GATOR_REGISTER_TRACE(probe_name) \
		register_trace_##probe_name(probe_##probe_name, NULL)
#	define GATOR_UNREGISTER_TRACE(probe_name) \
		unregister_trace_##probe_name(probe_##probe_name, NULL)
#endif

/******************************************************************************
 * Events
 ******************************************************************************/
struct __gator_interface {
	int  (*create_files)(struct super_block *sb, struct dentry *root);
	int  (*init)(int *key);
	int  (*start)(void);
	void (*stop)(void);
	void (*online)(void);
	void (*offline)(void);
	int  (*read)(int **buffer);
	struct __gator_interface *next;
};

typedef struct __gator_interface gator_interface;

int gator_event_install(int (*event_install)(gator_interface *));

extern unsigned long gator_net_traffic;

#endif // GATOR_H_