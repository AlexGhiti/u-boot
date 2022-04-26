#include <common.h>
#include <cpu.h>
#include <spl.h>

DECLARE_GLOBAL_DATA_PTR;

void *board_fdt_blob_setup(int *err)
{
	*err = 0;

	return (void *)(ulong)gd->arch.firmware_fdt_addr;
}

int board_init(void)
{
	/* https://lore.kernel.org/u-boot/31587574-4cd1-02da-9761-0134ac82b94b@sholland.org/ */
	return cpu_probe_all();
}

int ft_board_setup(void *blob, struct bd_info *bd)
{
	phys_addr_t base;
	phys_size_t size;

	/*
	 * boot0 detects RAM size at runtime so we need to pass this info to
	 * the kernel dtb (which can be different from the u-boot one).
	 */
	base = gd->ram_base;
	size = gd->ram_size;

	fdt_fixup_memory(blob, (u64)base, (u64)size);

	return 0;
}

uint32_t spl_boot_device(void)
{
	return BOOT_DEVICE_MMC1;
}
