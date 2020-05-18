#ifndef SERIALABSTRACT_H
#define SERIALABSTRACT_H

#include <libraries/StreamInterface.h>

#include "libraries/Global.h"
#include "libraries/Ring.h"

// TODO: pins and methods

class SerialAbstract : public StreamInterface {
 public:
  enum DataBits { Data5 = 0x00, Data6 = 0x20, Data7 = 0x40, Data8 = 0x60 };
  enum Parity {
    NoParity = 0x00,
    EvenParity = 0x06,
    OddParity = 0x02,
    MarkParity = 0x82,
    SpaceParity = 0x86
  };
  enum StopBits { OneStop = 0x00, TwoStop = 0x08 };
  enum Event { TransmittedData, ReceivedData };

  ~SerialAbstract() = default;
  void begin();
  void begin(int baudrate);
  void end();
  void setBaudRate(int baudrate);
  int baudrate() const;
  void setDataBits(DataBits dataBits);
  void setParity(Parity patity);
  void setStopBits(StopBits stopBits);
  DataBits dataBits() const;
  Parity parity() const;
  StopBits stopBits() const;
  virtual int available(void);
  virtual int peek(void);
  virtual int read(void);
  int availableForWrite(void);
  virtual void flush(void);
  virtual int write(unsigned char ch);
  virtual int write(const void* buf, int len);
  int write(unsigned long n) { return write(static_cast<unsigned char>(n)); }
  int write(long n) { return write(static_cast<unsigned char>(n)); }
  int write(unsigned int n) { return write(static_cast<unsigned char>(n)); }
  int write(int n) { return write(static_cast<unsigned char>(n)); }

 private:
  const uint _base;
  const uint _irq;
  Ring<uchar, 64> _ring;
  int _baudRate;
  DataBits _dataBits;
  Parity _parity;
  StopBits _stopBits;
};

#endif  // SERIALABSTRACT_H
