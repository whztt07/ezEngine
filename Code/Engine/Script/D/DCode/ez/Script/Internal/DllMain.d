module ez.script.internal.dllmain;

import core.sys.windows.dll;

mixin SimpleDllMain!(DllIsUsedFromC.no);