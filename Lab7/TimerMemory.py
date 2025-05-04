import time
import tracemalloc


class TimerMemory:  # pragma: no cover
    def __enter__(self):
        self.start = time.perf_counter()
        tracemalloc.start()

    def __exit__(self, exc_type, exc_value, traceback):
        current, peak = tracemalloc.get_traced_memory()
        tracemalloc.stop()
        print(f"[Timer] Executed in {time.perf_counter() - self.start:.6f} seconds")
        print(f"[Memory] Used max {peak / (1024 * 1024):.6f} MB")
