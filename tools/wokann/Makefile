MAKEFLAGS += --no-print-directory

WOKANTOOLDIRS := hashCal headerFix transMsg

# 默认目标
.PHONY: all $(WOKANTOOLDIRS) clean
all: $(WOKANTOOLDIRS)

# 编译规则 
$(WOKANTOOLDIRS):
	@$(MAKE) -C $@
	
# 清理规则
clean:
	@for dir in $(WOKANTOOLDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
