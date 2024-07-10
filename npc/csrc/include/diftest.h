// 在DUT host memory的`buf`和REF guest memory的`addr`之间拷贝`n`字节,
// `direction`指定拷贝的方向, `DIFFTEST_TO_DUT`表示往DUT拷贝, `DIFFTEST_TO_REF`表示往REF拷贝
extern "C" void difftest_memcpy(paddr_t addr, void *buf, size_t n, bool direction);
// `direction`为`DIFFTEST_TO_DUT`时, 获取REF的寄存器状态到`dut`;
extern "C" void difftest_regcpy(void *dut, bool direction);
// 让REF执行`n`条指令
extern "C" void difftest_exec(uint64_t n);
//为中断准备
extern "C" void difftest_raise_intr(word_t NO);
// 初始化REF的DiffTest功能
extern "C" void difftest_init(int port);

enum { DIFFTEST_TO_DUT, DIFFTEST_TO_REF };

