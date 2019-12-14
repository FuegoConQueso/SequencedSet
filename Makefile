CXX = g++
BUILDDIR = build/
objects = Block.o BlockBuffer.o FileManager.o Header.o HeaderBuffer.o Index.o IndexBuffer.o IndexRecord.o \
	 IndexRecordBuffer.o InputFileHeader.o rbuffer1.o Record.o SeqSetExceptions.o SequencedSet.o TestDriver.o
pobjects = $(addprefix $(BUILDDIR),$(objects))

$(BUILDDIR)TestDriver: $(pobjects)
	 $(CXX) -o $(BUILDDIR)TestDriver $(pobjects)
$(BUILDDIR)Block.o: Block.h Record.h rbuffer1.h SequencedSet.h
	 $(CXX) -c Block.cpp -o $(BUILDDIR)Block.o
$(BUILDDIR)BlockBuffer.o: BlockBuffer.h Block.h rbuffer1.h Record.h Header.h SequencedSet.h
	 $(CXX) -c BlockBuffer.cpp -o $(BUILDDIR)BlockBuffer.o
$(BUILDDIR)FileManager.o: FileManager.h Block.h Index.h SequencedSet.h Header.h HeaderBuffer.h
	 $(CXX) -c FileManager.cpp -o $(BUILDDIR)FileManager.o
$(BUILDDIR)Header.o: Header.h SequencedSet.h InputFileHeader.h
	 $(CXX) -c Header.cpp -o $(BUILDDIR)Header.o
$(BUILDDIR)HeaderBuffer.o: HeaderBuffer.h Header.h SequencedSet.h
	 $(CXX) -c HeaderBuffer.cpp -o $(BUILDDIR)HeaderBuffer.o
$(BUILDDIR)Index.o: Index.h IndexBuffer.h Record.h SequencedSet.h Header.h
	 $(CXX) -c Index.cpp -o $(BUILDDIR)Index.o
$(BUILDDIR)IndexBuffer.o: IndexBuffer.h SequencedSet.h IndexRecordBuffer.h Header.h
	 $(CXX) -c IndexBuffer.cpp -o $(BUILDDIR)IndexBuffer.o
$(BUILDDIR)IndexRecord.o: IndexRecord.h
	 $(CXX) -c IndexRecord.cpp -o $(BUILDDIR)IndexRecord.o
$(BUILDDIR)IndexRecordBuffer.o: IndexRecordBuffer.h IndexRecord.h SequencedSet.h Header.h
	 $(CXX) -c IndexRecordBuffer.cpp -o $(BUILDDIR)IndexRecordBuffer.o
$(BUILDDIR)InputFileHeader.o: InputFileHeader.h Header.h
	 $(CXX) -c InputFileHeader.cpp -o $(BUILDDIR)InputFileHeader.o
$(BUILDDIR)rbuffer1.o: rbuffer1.h Record.h SequencedSet.h Header.h
	 $(CXX) -c rbuffer1.cpp -o $(BUILDDIR)rbuffer1.o
$(BUILDDIR)Record.o: Record.h Header.h SequencedSet.h
	 $(CXX) -c Record.cpp -o $(BUILDDIR)Record.o
$(BUILDDIR)SeqSetExceptions.o:
	 $(CXX) -c SeqSetExceptions.cpp -o $(BUILDDIR)SeqSetExceptions.o
$(BUILDDIR)SequencedSet.o: SequencedSet.h InputFileHeader.h Block.h Index.h IndexBuffer.h Record.h BlockBuffer.h Header.h HeaderBuffer.h FileManager.h SeqSetExceptions.cpp
	 $(CXX) -c SequencedSet.cpp -o $(BUILDDIR)SequencedSet.o
$(BUILDDIR)TestDriver.o: SequencedSet.h Record.h Block.h
	 $(CXX) -c testDriver.cpp -o $(BUILDDIR)TestDriver.o
.PHONY : clean
clean :
	 rm TestDriver $(pobjects)