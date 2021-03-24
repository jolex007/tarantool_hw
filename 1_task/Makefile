all: build

build: sort.c coroutine/coroutine_impl.c coroutine/context/machine_context.S coroutine/context/machine_context.c queue/queue.c fibers/fiber.c queue/scheduler.c
	gcc -o sort sort.c coroutine/coroutine_impl.c coroutine/context/machine_context.S coroutine/context/machine_context.c queue/queue.c fibers/fiber.c queue/scheduler.c

sanitize_build: sort.c coroutine/coroutine_impl.c coroutine/context/machine_context.S coroutine/context/machine_context.c queue/queue.c fibers/fiber.c queue/scheduler.c
	clang -fsanitize=address -o sort sort.c coroutine/coroutine_impl.c coroutine/context/machine_context.S coroutine/context/machine_context.c queue/queue.c fibers/fiber.c queue/scheduler.c