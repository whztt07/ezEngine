﻿#include <PCH.h>
#include <Foundation/Containers/HybridArray.h>
#include <Foundation/Strings/String.h>

namespace HybridArrayTestDetail
{

  class Dummy
  {
  public:
    int a;
    std::string s;

    Dummy() : a(0), s("Test") { }
    Dummy(int a) : a(a), s("Test") { }
    Dummy(const Dummy& other) : a(other.a), s(other.s) { }
    ~Dummy() { }

    Dummy& operator=(const Dummy& other)
    {
      a = other.a;
      s = other.s;
      return *this;
    }

    bool operator<=(const Dummy& dummy) const { return a <= dummy.a; }
    bool operator>=(const Dummy& dummy) const { return a >= dummy.a; }
    bool operator>(const Dummy& dummy) const { return a > dummy.a; }
    bool operator<(const Dummy& dummy) const { return a < dummy.a; }
    bool operator==(const Dummy& dummy) const { return a == dummy.a; }
  };

  static ezHybridArray<ezConstructionCounter, 16> CreateArray(ezUInt32 uiSize, ezUInt32 uiOffset)
  {
    ezHybridArray<ezConstructionCounter, 16> a;
    a.SetCountUninitialized(uiSize);

    for (ezUInt32 i = 0; i < uiSize; ++i)
      a[i] = uiOffset + i;

    return a;
  }
}

#if EZ_ENABLED(EZ_PLATFORM_64BIT)
  EZ_CHECK_AT_COMPILETIME(sizeof(ezHybridArray<ezInt32, 1>) == 32);
#else
  EZ_CHECK_AT_COMPILETIME(sizeof(ezHybridArray<ezInt32, 1>) == 20);
#endif

EZ_CREATE_SIMPLE_TEST(Containers, HybridArray)
{
  EZ_TEST_BLOCK(ezTestBlock::Enabled, "Constructor")
  {
    ezHybridArray<ezInt32, 16> a1;
    ezHybridArray<ezConstructionCounter, 16> a2;

    EZ_TEST_BOOL(a1.GetCount() == 0);
    EZ_TEST_BOOL(a2.GetCount() == 0);
    EZ_TEST_BOOL(a1.IsEmpty());
    EZ_TEST_BOOL(a2.IsEmpty());
  }

  EZ_TEST_BLOCK(ezTestBlock::Enabled, "Copy Constructor")
  {
    ezHybridArray<ezInt32, 16> a1;

    EZ_TEST_BOOL(a1.GetHeapMemoryUsage() == 0);

    for (ezInt32 i = 0; i < 32; ++i)
    {
      a1.PushBack(rand() % 100000);

      if (i < 16)
      {
        EZ_TEST_BOOL(a1.GetHeapMemoryUsage() == 0);
      }
      else
      {
        EZ_TEST_BOOL(a1.GetHeapMemoryUsage() >= i * sizeof(ezInt32));
      }
    }

    ezHybridArray<ezInt32, 16> a2 = a1;
    ezHybridArray<ezInt32, 16> a3 (a1);

    EZ_TEST_BOOL(a1 == a2);
    EZ_TEST_BOOL(a1 == a3);
    EZ_TEST_BOOL(a2 == a3);

    ezInt32 test[] = { 1, 2, 3, 4 };
    ezArrayPtr<ezInt32> aptr(test);

    ezHybridArray<ezInt32, 16> a4(aptr);

    EZ_TEST_BOOL(a4 == aptr);
  }

  EZ_TEST_BLOCK(ezTestBlock::Enabled, "Move Constructor / Operator")
  {
    EZ_TEST_BOOL(ezConstructionCounter::HasAllDestructed());

    {
      // move constructor
      ezHybridArray<ezConstructionCounter, 16> a1 (HybridArrayTestDetail::CreateArray(100, 20));

      EZ_TEST_INT(a1.GetCount(), 100);
      for (ezUInt32 i = 0; i < a1.GetCount(); ++i)
        EZ_TEST_INT(a1[i].m_iData, 20 + i);

      // move operator
      a1 = HybridArrayTestDetail::CreateArray(200, 50);

      EZ_TEST_INT(a1.GetCount(), 200);
      for (ezUInt32 i = 0; i < a1.GetCount(); ++i)
        EZ_TEST_INT(a1[i].m_iData, 50 + i);
    }

    EZ_TEST_BOOL(ezConstructionCounter::HasAllDestructed());

    {
      // move constructor
      ezHybridArray<ezConstructionCounter, 16> a2 (HybridArrayTestDetail::CreateArray(10, 30));

      EZ_TEST_INT(a2.GetCount(), 10);
      for (ezUInt32 i = 0; i < a2.GetCount(); ++i)
        EZ_TEST_INT(a2[i].m_iData, 30 + i);

      // move operator
      a2 = HybridArrayTestDetail::CreateArray(8, 70);

      EZ_TEST_INT(a2.GetCount(), 8);
      for (ezUInt32 i = 0; i < a2.GetCount(); ++i)
        EZ_TEST_INT(a2[i].m_iData, 70 + i);
    }

    EZ_TEST_BOOL(ezConstructionCounter::HasAllDestructed());
  }

  EZ_TEST_BLOCK(ezTestBlock::Enabled, "Convert to ArrayPtr")
  {
    ezHybridArray<ezInt32, 16> a1;

    for (ezInt32 i = 0; i < 100; ++i)
    {
      ezInt32 r = rand() % 100000;
      a1.PushBack(r);
    }

    ezArrayPtr<ezInt32> ap = a1;

    EZ_TEST_BOOL(ap.GetCount () == a1.GetCount());
  }

  EZ_TEST_BLOCK(ezTestBlock::Enabled, "operator =")
  {
    ezHybridArray<ezInt32, 16> a1, a2;

    for (ezInt32 i = 0; i < 100; ++i)
      a1.PushBack(i);

    a2 = a1;

    EZ_TEST_BOOL(a1 == a2);

    ezArrayPtr<ezInt32> arrayPtr(a1);

    a2 = arrayPtr;

    EZ_TEST_BOOL(a2 == arrayPtr);
  }

  EZ_TEST_BLOCK(ezTestBlock::Enabled, "operator == / !=")
  {
    ezHybridArray<ezInt32, 16> a1, a2;

    EZ_TEST_BOOL(a1 == a1);
    EZ_TEST_BOOL(a2 == a2);
    EZ_TEST_BOOL(a1 == a2);

    EZ_TEST_BOOL((a1 != a1) == false);
    EZ_TEST_BOOL((a2 != a2) == false);
    EZ_TEST_BOOL((a1 != a2) == false);

    for (ezInt32 i = 0; i < 100; ++i)
    {
      ezInt32 r = rand() % 100000;
      a1.PushBack(r);
      a2.PushBack(r);
    }

    EZ_TEST_BOOL(a1 == a1);
    EZ_TEST_BOOL(a2 == a2);
    EZ_TEST_BOOL(a1 == a2);

    EZ_TEST_BOOL((a1 != a2) == false);
  }

  EZ_TEST_BLOCK(ezTestBlock::Enabled, "Index operator")
  {
    ezHybridArray<ezInt32, 16> a1;
    a1.SetCountUninitialized(100);

    for (ezInt32 i = 0; i < 100; ++i)
      a1[i] = i;

    for (ezInt32 i = 0; i < 100; ++i)
      EZ_TEST_INT(a1[i], i);

    const ezHybridArray<ezInt32, 16> ca1 = a1;

    for (ezInt32 i = 0; i < 100; ++i)
      EZ_TEST_INT(ca1[i], i);
  }

  EZ_TEST_BLOCK(ezTestBlock::Enabled, "SetCount / GetCount / IsEmpty")
  {
    ezHybridArray<ezInt32, 16> a1;

    EZ_TEST_BOOL(a1.IsEmpty());

    for (ezInt32 i = 0; i < 128; ++i)
    {
      a1.SetCount(i + 1);
      EZ_TEST_INT(a1[i], 0);
      a1[i] = i;

      EZ_TEST_INT(a1.GetCount(), i + 1);
      EZ_TEST_BOOL(!a1.IsEmpty());
    }

    for (ezInt32 i = 0; i < 128; ++i)
      EZ_TEST_INT(a1[i], i);

    for (ezInt32 i = 128; i >= 0; --i)
    {
      a1.SetCount(i);

      EZ_TEST_INT(a1.GetCount(), i);

      for (ezInt32 i2 = 0; i2 < i; ++i2)
        EZ_TEST_INT(a1[i2], i2);
    }

    EZ_TEST_BOOL(a1.IsEmpty());

    a1.SetCountUninitialized(32);
    EZ_TEST_INT(a1.GetCount(), 32);
    a1[31] = 45;
    EZ_TEST_INT(a1[31], 45);
  }

  EZ_TEST_BLOCK(ezTestBlock::Enabled, "Clear")
  {
    ezHybridArray<ezInt32, 16> a1;
    a1.Clear();

    a1.PushBack(3);
    a1.Clear();

    EZ_TEST_BOOL(a1.IsEmpty());
  }

  EZ_TEST_BLOCK(ezTestBlock::Enabled, "Contains / IndexOf / LastIndexOf")
  {
    ezHybridArray<ezInt32, 16> a1;

    for (ezInt32 i = -100; i < 100; ++i)
      EZ_TEST_BOOL(!a1.Contains(i));

    for (ezInt32 i = 0; i < 100; ++i)
      a1.PushBack(i);

    for (ezInt32 i = 0; i < 100; ++i)
    {
      EZ_TEST_BOOL(a1.Contains(i));
      EZ_TEST_INT(a1.IndexOf(i), i);
      EZ_TEST_INT(a1.LastIndexOf(i), i);
    }
  }

  EZ_TEST_BLOCK(ezTestBlock::Enabled, "Insert")
  {
    ezHybridArray<ezInt32, 16> a1;

    // always inserts at the front
    for (ezInt32 i = 0; i < 100; ++i)
      a1.Insert(i, 0);

    for (ezInt32 i = 0; i < 100; ++i)
      EZ_TEST_INT(a1[i], 99 - i);
  }

  EZ_TEST_BLOCK(ezTestBlock::Enabled, "Remove")
  {
    ezHybridArray<ezInt32, 16> a1;

    for (ezInt32 i = 0; i < 100; ++i)
      a1.PushBack(i % 2);

    while (a1.Remove(1))
    {
    }

    EZ_TEST_BOOL(a1.GetCount() == 50);

    for (ezUInt32 i = 0; i < a1.GetCount(); ++i)
      EZ_TEST_INT(a1[i], 0);
  }

  EZ_TEST_BLOCK(ezTestBlock::Enabled, "RemoveSwap")
  {
    ezHybridArray<ezInt32, 16> a1;

    for (ezInt32 i = 0; i < 10; ++i)
      a1.Insert(i, i); // inserts at the end

    a1.RemoveSwap(9);
    a1.RemoveSwap(7);
    a1.RemoveSwap(5);
    a1.RemoveSwap(3);
    a1.RemoveSwap(1);

    EZ_TEST_INT(a1.GetCount(), 5);

    for (ezInt32 i = 0; i < 5; ++i)
      EZ_TEST_BOOL(ezMath::IsEven(a1[i]));
  }

  EZ_TEST_BLOCK(ezTestBlock::Enabled, "RemoveAt")
  {
    ezHybridArray<ezInt32, 16> a1;

    for (ezInt32 i = 0; i < 10; ++i)
      a1.Insert(i, i); // inserts at the end

    a1.RemoveAt(9);
    a1.RemoveAt(7);
    a1.RemoveAt(5);
    a1.RemoveAt(3);
    a1.RemoveAt(1);

    EZ_TEST_INT(a1.GetCount(), 5);

    for (ezInt32 i = 0; i < 5; ++i)
      EZ_TEST_INT(a1[i], i * 2);
  }

  EZ_TEST_BLOCK(ezTestBlock::Enabled, "RemoveAtSwap")
  {
    ezHybridArray<ezInt32, 16> a1;

    for (ezInt32 i = 0; i < 10; ++i)
      a1.Insert(i, i); // inserts at the end

    a1.RemoveAtSwap(9);
    a1.RemoveAtSwap(7);
    a1.RemoveAtSwap(5);
    a1.RemoveAtSwap(3);
    a1.RemoveAtSwap(1);

    EZ_TEST_INT(a1.GetCount(), 5);

    for (ezInt32 i = 0; i < 5; ++i)
      EZ_TEST_BOOL(ezMath::IsEven(a1[i]));
  }

  EZ_TEST_BLOCK(ezTestBlock::Enabled, "PushBack / PopBack / PeekBack")
  {
    ezHybridArray<ezInt32, 16> a1;

    for (ezInt32 i = 0; i < 10; ++i)
    {
      a1.PushBack(i);
      EZ_TEST_INT(a1.PeekBack(), i);
    }

    for (ezInt32 i = 9; i >= 0; --i)
    {
      EZ_TEST_INT(a1.PeekBack(), i);
      a1.PopBack();
    }

    a1.PushBack(23);
    a1.PushBack(2);
    a1.PushBack(3);

    a1.PopBack(2);
    EZ_TEST_INT(a1.PeekBack(), 23);
  }

  EZ_TEST_BLOCK(ezTestBlock::Enabled, "ExpandAndGetRef")
  {
    ezHybridArray<ezInt32, 16> a1;

    for (ezInt32 i = 0; i < 20; ++i)
    {
      ezInt32& intRef = a1.ExpandAndGetRef();
      intRef = i * 5;
    }


    EZ_TEST_BOOL(a1.GetCount() == 20);

    for (ezInt32 i = 0; i < 20; ++i)
    {
      EZ_TEST_INT(a1[i], i * 5);
    }
  }

  EZ_TEST_BLOCK(ezTestBlock::Enabled, "Construction / Destruction")
  {
    {
      EZ_TEST_BOOL(ezConstructionCounter::HasAllDestructed());

      ezHybridArray<ezConstructionCounter, 16> a1;
      ezHybridArray<ezConstructionCounter, 16> a2;

      EZ_TEST_BOOL(ezConstructionCounter::HasDone(0, 0)); // nothing has been constructed / destructed in between
      EZ_TEST_BOOL(ezConstructionCounter::HasAllDestructed());

      a1.PushBack(ezConstructionCounter(1));
      EZ_TEST_BOOL(ezConstructionCounter::HasDone(2, 1)); // one temporary, one final (copy constructed)

      a1.Insert(ezConstructionCounter(2), 0);
      EZ_TEST_BOOL(ezConstructionCounter::HasDone(2, 1)); // one temporary, one final (copy constructed)

      a2 = a1;
      EZ_TEST_BOOL(ezConstructionCounter::HasDone(2, 0)); // two copies

      a1.Clear();
      EZ_TEST_BOOL(ezConstructionCounter::HasDone(0, 2));

      a1.PushBack(ezConstructionCounter(3));
      a1.PushBack(ezConstructionCounter(4));
      a1.PushBack(ezConstructionCounter(5));
      a1.PushBack(ezConstructionCounter(6));

      EZ_TEST_BOOL(ezConstructionCounter::HasDone(8, 4)); // four temporaries

      a1.Remove(ezConstructionCounter(3));
      EZ_TEST_BOOL(ezConstructionCounter::HasDone(1, 2)); // one temporary, one destroyed

      a1.Remove(ezConstructionCounter(3));
      EZ_TEST_BOOL(ezConstructionCounter::HasDone(1, 1)); // one temporary, none destroyed

      a1.RemoveAt(0);
      EZ_TEST_BOOL(ezConstructionCounter::HasDone(0, 1)); // one destroyed

      a1.RemoveAtSwap(0);
      EZ_TEST_BOOL(ezConstructionCounter::HasDone(0, 1)); // one destroyed
    }

    // tests the destructor of a2 and a1
    EZ_TEST_BOOL(ezConstructionCounter::HasAllDestructed());
  }

  EZ_TEST_BLOCK(ezTestBlock::Enabled, "Compact")
  {
    ezHybridArray<ezInt32, 16> a;

    for (ezInt32 i = 0; i < 1000; ++i)
    {
      a.PushBack(i);
      EZ_TEST_INT(a.GetCount(), i + 1);
    }

    EZ_TEST_BOOL(a.GetHeapMemoryUsage() > 0);
    a.Compact();
    EZ_TEST_BOOL(a.GetHeapMemoryUsage() > 0);

    for (ezInt32 i = 0; i < 1000; ++i)
      EZ_TEST_INT(a[i], i);

    // this tests whether the static array is reused properly (well, I stepped through it in the debugger to check it)
    a.SetCount(15);
    a.Compact();
    EZ_TEST_BOOL(a.GetHeapMemoryUsage() == 0);

    for (ezInt32 i = 0; i < 15; ++i)
      EZ_TEST_INT(a[i], i);

    a.Clear();
    a.Compact();
    EZ_TEST_BOOL(a.GetHeapMemoryUsage() == 0);
  }

  EZ_TEST_BLOCK(ezTestBlock::Enabled, "SortingPrimitives")
  {
    ezHybridArray<ezUInt32, 16> list;

    list.Sort();

    for (ezUInt32 i = 0; i < 45; i++)
    {
      list.PushBack(std::rand());
    }
    list.Sort();

    ezUInt32 last = 0;
    for (ezUInt32 i = 0; i < list.GetCount(); i++)
    {
      EZ_TEST_BOOL(last <= list[i]);
      last = list[i];
    }
  }

  EZ_TEST_BLOCK(ezTestBlock::Enabled, "SortingObjects")
  {
    ezHybridArray<HybridArrayTestDetail::Dummy, 16> list;
    list.Reserve(128);

    for (ezUInt32 i = 0; i < 100; i++)
    {
      list.PushBack(HybridArrayTestDetail::Dummy(rand()));
    }
    list.Sort();

    HybridArrayTestDetail::Dummy last = 0;
    for (ezUInt32 i = 0; i < list.GetCount(); i++)
    {
      EZ_TEST_BOOL(last <= list[i]);
      last = list[i];
    }
  }

  EZ_TEST_BLOCK(ezTestBlock::Enabled, "Various")
  {
    ezHybridArray<HybridArrayTestDetail::Dummy, 16> list;
    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);
    list.Insert(4, 3);
    list.Insert(0, 1);
    list.Insert(0, 5);

    EZ_TEST_BOOL(list[0].a == 1);
    EZ_TEST_BOOL(list[1].a == 0);
    EZ_TEST_BOOL(list[2].a == 2);
    EZ_TEST_BOOL(list[3].a == 3);
    EZ_TEST_BOOL(list[4].a == 4);
    EZ_TEST_BOOL(list[5].a == 0);
    EZ_TEST_BOOL(list.GetCount() == 6);

    list.RemoveAt(3);
    list.RemoveAtSwap(2);

    EZ_TEST_BOOL(list[0].a == 1);
    EZ_TEST_BOOL(list[1].a == 0);
    EZ_TEST_BOOL(list[2].a == 0);
    EZ_TEST_BOOL(list[3].a == 4);
    EZ_TEST_BOOL(list.GetCount() == 4);
    EZ_TEST_BOOL(list.IndexOf(0) == 1);
    EZ_TEST_BOOL(list.LastIndexOf(0) == 2);

    list.PushBack(5);
    EZ_TEST_BOOL(list[4].a == 5);
    HybridArrayTestDetail::Dummy d = list.PeekBack();
    list.PopBack();
    EZ_TEST_BOOL(d.a == 5);
    EZ_TEST_BOOL(list.GetCount() == 4);
  }

  EZ_TEST_BLOCK(ezTestBlock::Enabled, "Assignment")
  {
    ezHybridArray<HybridArrayTestDetail::Dummy, 16> list;
    for (int i = 0; i < 16; i++)
    {
      list.PushBack(HybridArrayTestDetail::Dummy(rand()));
    }

    ezHybridArray<HybridArrayTestDetail::Dummy, 16> list2;
    for (int i = 0; i < 8; i++)
    {
      list2.PushBack(HybridArrayTestDetail::Dummy(rand()));
    }

    list = list2;
    EZ_TEST_BOOL(list.GetCount() == list2.GetCount());

    list2.Clear();
    EZ_TEST_BOOL(list2.GetCount() == 0);

    list2 = list;
    EZ_TEST_BOOL(list.PeekBack() == list2.PeekBack());
    EZ_TEST_BOOL(list == list2);

    for (int i = 0; i < 16; i++)
    {
      list2.PushBack(HybridArrayTestDetail::Dummy(rand()));
    }

    list = list2;
    EZ_TEST_BOOL(list.PeekBack() == list2.PeekBack());
    EZ_TEST_BOOL(list == list2);
  }

  EZ_TEST_BLOCK(ezTestBlock::Enabled, "Count")
  {
    ezHybridArray<HybridArrayTestDetail::Dummy, 16> list;
    for (int i = 0; i < 16; i++)
    {
      list.PushBack(HybridArrayTestDetail::Dummy(rand()));
    }
    list.SetCount(32);
    list.SetCount(4);

    list.Compact();
  }

  EZ_TEST_BLOCK(ezTestBlock::Enabled, "Reserve")
  {
    EZ_TEST_BOOL(ezConstructionCounter::HasAllDestructed());

    ezHybridArray<ezConstructionCounter, 16> a;

    EZ_TEST_BOOL(ezConstructionCounter::HasDone(0, 0)); // nothing has been constructed / destructed in between
    EZ_TEST_BOOL(ezConstructionCounter::HasAllDestructed());

    a.Reserve(100);

    EZ_TEST_BOOL(ezConstructionCounter::HasDone(0, 0)); // nothing has been constructed / destructed in between
    EZ_TEST_BOOL(ezConstructionCounter::HasAllDestructed());

    a.SetCount(10);
    EZ_TEST_BOOL(ezConstructionCounter::HasDone(10, 0));

    a.Reserve(100);
    EZ_TEST_BOOL(ezConstructionCounter::HasDone(0, 0));

    a.SetCount(100);
    EZ_TEST_BOOL(ezConstructionCounter::HasDone(90, 0));

    a.Reserve(200);
    EZ_TEST_BOOL(ezConstructionCounter::HasDone(100, 100)); // had to copy some elements over

    a.SetCount(200);
    EZ_TEST_BOOL(ezConstructionCounter::HasDone(100, 0));
  }

  EZ_TEST_BLOCK(ezTestBlock::Enabled, "Compact")
  {
    EZ_TEST_BOOL(ezConstructionCounter::HasAllDestructed());

    ezHybridArray<ezConstructionCounter, 16> a;

    EZ_TEST_BOOL(ezConstructionCounter::HasDone(0, 0)); // nothing has been constructed / destructed in between
    EZ_TEST_BOOL(ezConstructionCounter::HasAllDestructed());

    a.SetCount(100);
    EZ_TEST_BOOL(ezConstructionCounter::HasDone(100, 0));

    a.SetCount(200);
    EZ_TEST_BOOL(ezConstructionCounter::HasDone(200, 100));

    a.SetCount(10);
    EZ_TEST_BOOL(ezConstructionCounter::HasDone(0, 190));

    // no reallocations and copying, if the memory is already available
    a.SetCount(200);
    EZ_TEST_BOOL(ezConstructionCounter::HasDone(190, 0));

    a.SetCount(10);
    EZ_TEST_BOOL(ezConstructionCounter::HasDone(0, 190));

    // now we remove the spare memory
    a.Compact();
    EZ_TEST_BOOL(ezConstructionCounter::HasDone(10, 10));

    // this time the array needs to be relocated, and thus the already present elements need to be copied
    a.SetCount(200);
    EZ_TEST_BOOL(ezConstructionCounter::HasDone(200, 10));

    // this does not deallocate memory
    a.Clear();
    EZ_TEST_BOOL(ezConstructionCounter::HasDone(0, 200));

    a.SetCount(100);
    EZ_TEST_BOOL(ezConstructionCounter::HasDone(100, 0));

    // therefore no object relocation
    a.SetCount(200);
    EZ_TEST_BOOL(ezConstructionCounter::HasDone(100, 0));

    a.Clear();
    EZ_TEST_BOOL(ezConstructionCounter::HasDone(0, 200));

    // this will deallocate ALL memory
    a.Compact();

    a.SetCount(100);
    EZ_TEST_BOOL(ezConstructionCounter::HasDone(100, 0));

    // this time objects need to be relocated
    a.SetCount(200);
    EZ_TEST_BOOL(ezConstructionCounter::HasDone(200, 100));
  }

  EZ_TEST_BLOCK(ezTestBlock::Enabled, "STL Iterator")
  {
    ezHybridArray<ezInt32, 16> a1;

    for (ezInt32 i = 0; i < 1000; ++i)
      a1.PushBack(1000 - i - 1);

    // STL sort
    std::sort(begin(a1), end(a1));

    for (ezInt32 i = 1; i < 1000; ++i)
    {
      EZ_TEST_BOOL(a1[i - 1] <= a1[i]);
    }

    // foreach
    ezUInt32 prev = 0;
    for(ezUInt32 val : a1)
    {
      EZ_TEST_BOOL(prev <= val);
      prev = val;
    }

    // const array
    const ezHybridArray<ezInt32, 16>& a2 = a1;

    // STL lower bound
    auto lb = std::lower_bound(begin(a2), end(a2), 400);
    EZ_TEST_BOOL(*lb == a2[400]);
  }

  EZ_TEST_BLOCK(ezTestBlock::Enabled, "STL Reverse Iterator")
  {
    ezHybridArray<ezInt32, 16> a1;

    for (ezInt32 i = 0; i < 1000; ++i)
      a1.PushBack(1000 - i - 1);

    // STL sort
    std::sort(rbegin(a1), rend(a1));

    for (ezInt32 i = 1; i < 1000; ++i)
    {
      EZ_TEST_BOOL(a1[i - 1] >= a1[i]);
    }

    // foreach
    ezUInt32 prev = 1000;
    for(ezUInt32 val : a1)
    {
      EZ_TEST_BOOL(prev >= val);
      prev = val;
    }

    // const array
    const ezHybridArray<ezInt32, 16>& a2 = a1;

    // STL lower bound
    auto lb = std::lower_bound(rbegin(a2), rend(a2), 400);
    EZ_TEST_BOOL(*lb == a2[1000 - 400 - 1]);
  }

  EZ_TEST_BLOCK(ezTestBlock::Enabled, "Swap")
  {
    ezHybridArray<ezInt32, 8> a1, a2;

    ezInt32 content1[] = { 1, 2, 3, 4 };
    ezInt32 content2[] = { 5, 6, 7, 8, 9 };

    a1 = ezMakeArrayPtr(content1);
    a2 = ezMakeArrayPtr(content2);

    ezInt32* a1Ptr = a1.GetData();
    ezInt32* a2Ptr = a2.GetData();

    a1.Swap(a2);

    // Because the data points to the internal storage the pointers shouldn't change when swapping
    EZ_TEST_BOOL(a1Ptr == a1.GetData());
    EZ_TEST_BOOL(a2Ptr == a2.GetData());

    // The data however should be swapped
    EZ_TEST_BOOL(a1.GetArrayPtr() == ezMakeArrayPtr(content2));
    EZ_TEST_BOOL(a2.GetArrayPtr() == ezMakeArrayPtr(content1));
  }
}

