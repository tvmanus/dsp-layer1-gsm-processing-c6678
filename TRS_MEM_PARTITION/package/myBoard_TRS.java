/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y25
 */
import java.util.*;
import org.mozilla.javascript.*;
import xdc.services.intern.xsr.*;
import xdc.services.spec.Session;

public class myBoard_TRS
{
    static final String VERS = "@(#) xdc-y25\n";

    static final Proto.Elm $$T_Bool = Proto.Elm.newBool();
    static final Proto.Elm $$T_Num = Proto.Elm.newNum();
    static final Proto.Elm $$T_Str = Proto.Elm.newStr();
    static final Proto.Elm $$T_Obj = Proto.Elm.newObj();

    static final Proto.Fxn $$T_Met = new Proto.Fxn(null, null, 0, -1, false);
    static final Proto.Map $$T_Map = new Proto.Map($$T_Obj);
    static final Proto.Arr $$T_Vec = new Proto.Arr($$T_Obj);

    static final XScriptO $$DEFAULT = Value.DEFAULT;
    static final Object $$UNDEF = Undefined.instance;

    static final Proto.Obj $$Package = (Proto.Obj)Global.get("$$Package");
    static final Proto.Obj $$Module = (Proto.Obj)Global.get("$$Module");
    static final Proto.Obj $$Instance = (Proto.Obj)Global.get("$$Instance");
    static final Proto.Obj $$Params = (Proto.Obj)Global.get("$$Params");

    static final Object $$objFldGet = Global.get("$$objFldGet");
    static final Object $$objFldSet = Global.get("$$objFldSet");
    static final Object $$proxyGet = Global.get("$$proxyGet");
    static final Object $$proxySet = Global.get("$$proxySet");
    static final Object $$delegGet = Global.get("$$delegGet");
    static final Object $$delegSet = Global.get("$$delegSet");

    Scriptable xdcO;
    Session ses;
    Value.Obj om;

    boolean isROV;
    boolean isCFG;

    Proto.Obj pkgP;
    Value.Obj pkgV;

    ArrayList<Object> imports = new ArrayList<Object>();
    ArrayList<Object> loggables = new ArrayList<Object>();
    ArrayList<Object> mcfgs = new ArrayList<Object>();
    ArrayList<Object> icfgs = new ArrayList<Object>();
    ArrayList<String> inherits = new ArrayList<String>();
    ArrayList<Object> proxies = new ArrayList<Object>();
    ArrayList<Object> sizes = new ArrayList<Object>();
    ArrayList<Object> tdefs = new ArrayList<Object>();

    void $$IMPORTS()
    {
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
        Global.callFxn("loadPackage", xdcO, "xdc.platform");
        Global.callFxn("loadPackage", xdcO, "ti.platforms.generic");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("myBoard_TRS.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("myBoard_TRS", new Value.Obj("myBoard_TRS", pkgP));
    }

    void Platform$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("myBoard_TRS.Platform.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("myBoard_TRS.Platform", new Value.Obj("myBoard_TRS.Platform", po));
        pkgV.bind("Platform", vo);
        // decls 
        om.bind("myBoard_TRS.Platform.Board", om.findStrict("xdc.platform.IPlatform.Board", "myBoard_TRS"));
        om.bind("myBoard_TRS.Platform.Memory", om.findStrict("xdc.platform.IPlatform.Memory", "myBoard_TRS"));
        // insts 
        Object insP = om.bind("myBoard_TRS.Platform.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("myBoard_TRS.Platform$$Object", new Proto.Obj());
        Object objP = om.bind("myBoard_TRS.Platform.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("myBoard_TRS.Platform$$Params", new Proto.Obj());
        om.bind("myBoard_TRS.Platform.Params", new Proto.Str(po, true));
    }

    void Platform$$CONSTS()
    {
        // module Platform
    }

    void Platform$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("myBoard_TRS.Platform$$create", new Proto.Fxn(om.findStrict("myBoard_TRS.Platform.Module", "myBoard_TRS"), om.findStrict("myBoard_TRS.Platform.Instance", "myBoard_TRS"), 3, 2, false));
                fxn.addArg(0, "name", $$T_Str, $$UNDEF);
                fxn.addArg(1, "args", $$T_Obj, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("myBoard_TRS.Platform.Params", "myBoard_TRS"), Global.newObject());
        sb = new StringBuilder();
        sb.append("myBoard_TRS$Platform$$create = function( name, args, __params ) {\n");
            sb.append("var __mod = xdc.om['myBoard_TRS.Platform'];\n");
            sb.append("var __inst = xdc.om['myBoard_TRS.Platform.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['myBoard_TRS']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {name:name, args:args});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("__inst.externalMemoryMap = __mod.PARAMS.externalMemoryMap;\n");
            sb.append("__inst.customMemoryMap = __mod.PARAMS.customMemoryMap;\n");
            sb.append("__inst.renameMap = __mod.PARAMS.renameMap;\n");
            sb.append("__inst.dataMemory = __mod.PARAMS.dataMemory;\n");
            sb.append("__inst.codeMemory = __mod.PARAMS.codeMemory;\n");
            sb.append("__inst.stackMemory = __mod.PARAMS.stackMemory;\n");
            sb.append("__inst.sectMap = __mod.PARAMS.sectMap;\n");
            sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [name, args]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("myBoard_TRS.Platform$$construct", new Proto.Fxn(om.findStrict("myBoard_TRS.Platform.Module", "myBoard_TRS"), null, 4, 2, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("myBoard_TRS.Platform$$Object", "myBoard_TRS"), null);
                fxn.addArg(1, "name", $$T_Str, $$UNDEF);
                fxn.addArg(2, "args", $$T_Obj, $$UNDEF);
                fxn.addArg(3, "__params", (Proto)om.findStrict("myBoard_TRS.Platform.Params", "myBoard_TRS"), Global.newObject());
        sb = new StringBuilder();
        sb.append("myBoard_TRS$Platform$$construct = function( __obj, name, args, __params ) {\n");
            sb.append("var __mod = xdc.om['myBoard_TRS.Platform'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {name:name, args:args});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("__inst.externalMemoryMap = __mod.PARAMS.externalMemoryMap;\n");
            sb.append("__inst.customMemoryMap = __mod.PARAMS.customMemoryMap;\n");
            sb.append("__inst.renameMap = __mod.PARAMS.renameMap;\n");
            sb.append("__inst.dataMemory = __mod.PARAMS.dataMemory;\n");
            sb.append("__inst.codeMemory = __mod.PARAMS.codeMemory;\n");
            sb.append("__inst.stackMemory = __mod.PARAMS.stackMemory;\n");
            sb.append("__inst.sectMap = __mod.PARAMS.sectMap;\n");
            sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void Platform$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Platform$$SIZES()
    {
    }

    void Platform$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "myBoard_TRS/Platform.xs");
        om.bind("myBoard_TRS.Platform$$capsule", cap);
        po = (Proto.Obj)om.findStrict("myBoard_TRS.Platform.Module", "myBoard_TRS");
        po.init("myBoard_TRS.Platform.Module", om.findStrict("xdc.platform.IPlatform.Module", "myBoard_TRS"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("CPU", (Proto)om.findStrict("ti.platforms.generic.Platform.Instance", "myBoard_TRS"), $$UNDEF, "wh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("myBoard_TRS.Platform$$create", "myBoard_TRS"), Global.get("myBoard_TRS$Platform$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("myBoard_TRS.Platform$$construct", "myBoard_TRS"), Global.get("myBoard_TRS$Platform$$construct"));
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("myBoard_TRS.Platform$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("myBoard_TRS.Platform$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("myBoard_TRS.Platform$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("myBoard_TRS.Platform$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("myBoard_TRS.Platform.Instance", "myBoard_TRS");
        po.init("myBoard_TRS.Platform.Instance", om.findStrict("xdc.platform.IPlatform.Instance", "myBoard_TRS"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("codeMemory", $$T_Str, "C0_PROG_RAM", "wh");
        po.addFld("dataMemory", $$T_Str, "C0_DATA_RAM", "wh");
        po.addFld("stackMemory", $$T_Str, "C3_DATA_RAM", "wh");
                fxn = Global.get(cap, "getCpuDataSheet");
                if (fxn != null) po.addFxn("getCpuDataSheet", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getCpuDataSheet", "myBoard_TRS"), fxn);
                fxn = Global.get(cap, "getCreateArgs");
                if (fxn != null) po.addFxn("getCreateArgs", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getCreateArgs", "myBoard_TRS"), fxn);
                fxn = Global.get(cap, "getExeContext");
                if (fxn != null) po.addFxn("getExeContext", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getExeContext", "myBoard_TRS"), fxn);
                fxn = Global.get(cap, "getExecCmd");
                if (fxn != null) po.addFxn("getExecCmd", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getExecCmd", "myBoard_TRS"), fxn);
                fxn = Global.get(cap, "getLinkTemplate");
                if (fxn != null) po.addFxn("getLinkTemplate", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getLinkTemplate", "myBoard_TRS"), fxn);
        po = (Proto.Obj)om.findStrict("myBoard_TRS.Platform$$Params", "myBoard_TRS");
        po.init("myBoard_TRS.Platform.Params", om.findStrict("xdc.platform.IPlatform$$Params", "myBoard_TRS"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("codeMemory", $$T_Str, "C0_PROG_RAM", "wh");
        po.addFld("dataMemory", $$T_Str, "C0_DATA_RAM", "wh");
        po.addFld("stackMemory", $$T_Str, "C3_DATA_RAM", "wh");
        po = (Proto.Obj)om.findStrict("myBoard_TRS.Platform$$Object", "myBoard_TRS");
        po.init("myBoard_TRS.Platform.Object", om.findStrict("myBoard_TRS.Platform.Instance", "myBoard_TRS"));
                fxn = Global.get(cap, "getCpuDataSheet");
                if (fxn != null) po.addFxn("getCpuDataSheet", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getCpuDataSheet", "myBoard_TRS"), fxn);
                fxn = Global.get(cap, "getCreateArgs");
                if (fxn != null) po.addFxn("getCreateArgs", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getCreateArgs", "myBoard_TRS"), fxn);
                fxn = Global.get(cap, "getExeContext");
                if (fxn != null) po.addFxn("getExeContext", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getExeContext", "myBoard_TRS"), fxn);
                fxn = Global.get(cap, "getExecCmd");
                if (fxn != null) po.addFxn("getExecCmd", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getExecCmd", "myBoard_TRS"), fxn);
                fxn = Global.get(cap, "getLinkTemplate");
                if (fxn != null) po.addFxn("getLinkTemplate", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getLinkTemplate", "myBoard_TRS"), fxn);
    }

    void Platform$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("myBoard_TRS.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "myBoard_TRS"));
        pkgP.bind("$capsule", $$UNDEF);
        pkgV.init2(pkgP, "myBoard_TRS", Value.DEFAULT, false);
        pkgV.bind("$name", "myBoard_TRS");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "myBoard_TRS.");
        pkgV.bind("$vers", Global.newArray());
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['myBoard_TRS'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void Platform$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("myBoard_TRS.Platform", "myBoard_TRS");
        po = (Proto.Obj)om.findStrict("myBoard_TRS.Platform.Module", "myBoard_TRS");
        vo.init2(po, "myBoard_TRS.Platform", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("myBoard_TRS.Platform$$capsule", "myBoard_TRS"));
        vo.bind("Instance", om.findStrict("myBoard_TRS.Platform.Instance", "myBoard_TRS"));
        vo.bind("Params", om.findStrict("myBoard_TRS.Platform.Params", "myBoard_TRS"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("myBoard_TRS.Platform.Params", "myBoard_TRS")).newInstance());
        vo.bind("$package", om.findStrict("myBoard_TRS", "myBoard_TRS"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("Board", om.findStrict("xdc.platform.IPlatform.Board", "myBoard_TRS"));
        tdefs.add(om.findStrict("xdc.platform.IPlatform.Board", "myBoard_TRS"));
        vo.bind("Memory", om.findStrict("xdc.platform.IPlatform.Memory", "myBoard_TRS"));
        tdefs.add(om.findStrict("xdc.platform.IPlatform.Memory", "myBoard_TRS"));
        vo.bind("MemoryMap", om.findStrict("xdc.platform.IPlatform.MemoryMap", "myBoard_TRS"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.platform");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "myBoard_TRS")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("myBoard_TRS.Platform$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("myBoard_TRS.Platform.Object", "myBoard_TRS"));
        pkgV.bind("Platform", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Platform");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("myBoard_TRS.Platform", "myBoard_TRS"));
        vo = (Value.Obj)om.findStrict("myBoard_TRS.Platform", "myBoard_TRS");
        Global.put(vo, "CPU", Global.callFxn("create", (Scriptable)om.find("ti.platforms.generic.Platform"), "CPU", Global.newObject("clockRate", 1000L, "catalogName", "ti.catalog.c6000", "deviceName", "TMS320C6678", "customMemoryMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"L1D_RAM", Global.newObject("name", "L1D_RAM", "base", 0x00F00000L, "len", 0x8000L, "space", "data", "access", "RW")}), Global.newArray(new Object[]{"L1P_RAM", Global.newObject("name", "L1P_RAM", "base", 0x00E00000L, "len", 0x8000L, "space", "code", "access", "RWX")}), Global.newArray(new Object[]{"L2RAM", Global.newObject("name", "L2RAM", "base", 0x00820000L, "len", 0x0005FFFFL, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"L2HEAP", Global.newObject("name", "L2HEAP", "base", 0x00800000L, "len", 0x00020000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"C1_L2RAM_INSHARED", Global.newObject("name", "C1_L2RAM_INSHARED", "base", 0xC000000L, "len", 0x00046000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"C2_L2RAM_INSHARED", Global.newObject("name", "C2_L2RAM_INSHARED", "base", 0xC046000L, "len", 0x00046000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"C3_L2RAM_INSHARED", Global.newObject("name", "C3_L2RAM_INSHARED", "base", 0xC08C000L, "len", 0x00046000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"C4_L2RAM_INSHARED", Global.newObject("name", "C4_L2RAM_INSHARED", "base", 0xC0D2000L, "len", 0x00046000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"C5_L2RAM_INSHARED", Global.newObject("name", "C5_L2RAM_INSHARED", "base", 0xC118000L, "len", 0x00046000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"C6_L2RAM_INSHARED", Global.newObject("name", "C6_L2RAM_INSHARED", "base", 0xC15E000L, "len", 0x00046000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"C7_L2RAM_INSHARED", Global.newObject("name", "C7_L2RAM_INSHARED", "base", 0xC1A4000L, "len", 0x00046000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"C1_SCRATCH_INSHARED", Global.newObject("name", "C1_SCRATCH_INSHARED", "base", 0xC1EA00AL, "len", 0x00032000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"C2_SCRATCH_INSHARED", Global.newObject("name", "C2_SCRATCH_INSHARED", "base", 0xC21C00AL, "len", 0x00032000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"C3_SCRATCH_INSHARED", Global.newObject("name", "C3_SCRATCH_INSHARED", "base", 0xC24E00AL, "len", 0x00032000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"C4_SCRATCH_INSHARED", Global.newObject("name", "C4_SCRATCH_INSHARED", "base", 0xC28000AL, "len", 0x00032000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"C5_SCRATCH_INSHARED", Global.newObject("name", "C5_SCRATCH_INSHARED", "base", 0xC2B200AL, "len", 0x00032000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"C6_SCRATCH_INSHARED", Global.newObject("name", "C6_SCRATCH_INSHARED", "base", 0xC2E400AL, "len", 0x00032000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"C7_SCRATCH_INSHARED", Global.newObject("name", "C7_SCRATCH_INSHARED", "base", 0xC31600AL, "len", 0x00032000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"C0_HEAP_RAM", Global.newObject("name", "C0_HEAP_RAM", "base", 0x80000000L, "len", 0x3200000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"C0_DATA_RAM", Global.newObject("name", "C0_DATA_RAM", "base", 0x83200000L, "len", 0x3200000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"C0_PROG_RAM", Global.newObject("name", "C0_PROG_RAM", "base", 0x86400000L, "len", 0x3200000L, "space", "code", "access", "RWX")}), Global.newArray(new Object[]{"C1_HEAP_RAM", Global.newObject("name", "C1_HEAP_RAM", "base", 0x90000000L, "len", 0x3200000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"C1_DATA_RAM", Global.newObject("name", "C1_DATA_RAM", "base", 0x93200000L, "len", 0x3200000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"C1_PROG_RAM", Global.newObject("name", "C1_PROG_RAM", "base", 0x96400000L, "len", 0x3200000L, "space", "code", "access", "RWX")}), Global.newArray(new Object[]{"C2_HEAP_RAM", Global.newObject("name", "C2_HEAP_RAM", "base", 0xA0000000L, "len", 0x3200000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"C2_DATA_RAM", Global.newObject("name", "C2_DATA_RAM", "base", 0xA3200000L, "len", 0x3200000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"C2_PROG_RAM", Global.newObject("name", "C2_PROG_RAM", "base", 0xA6400000L, "len", 0x3200000L, "space", "code", "access", "RWX")}), Global.newArray(new Object[]{"C3_HEAP_RAM", Global.newObject("name", "C3_HEAP_RAM", "base", 0xB0000000L, "len", 0x3200000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"C3_DATA_RAM", Global.newObject("name", "C3_DATA_RAM", "base", 0xB3200000L, "len", 0x3200000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"C3_PROG_RAM", Global.newObject("name", "C3_PROG_RAM", "base", 0xB6400000L, "len", 0x3200000L, "space", "code", "access", "RWX")}), Global.newArray(new Object[]{"C4_HEAP_RAM", Global.newObject("name", "C4_HEAP_RAM", "base", 0xc0000000L, "len", 0x3200000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"C4_DATA_RAM", Global.newObject("name", "C4_DATA_RAM", "base", 0xC3200000L, "len", 0x3200000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"C4_PROG_RAM", Global.newObject("name", "C4_PROG_RAM", "base", 0xC6400000L, "len", 0x3200000L, "space", "code", "access", "RWX")}), Global.newArray(new Object[]{"C5_HEAP_RAM", Global.newObject("name", "C5_HEAP_RAM", "base", 0xD0000000L, "len", 0x3200000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"C5_DATA_RAM", Global.newObject("name", "C5_DATA_RAM", "base", 0xD3200000L, "len", 0x3200000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"C5_PROG_RAM", Global.newObject("name", "C5_PROG_RAM", "base", 0xD6400000L, "len", 0x3200000L, "space", "code", "access", "RWX")}), Global.newArray(new Object[]{"C6_HEAP_RAM", Global.newObject("name", "C6_HEAP_RAM", "base", 0xE0000000L, "len", 0x3200000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"C6_DATA_RAM", Global.newObject("name", "C6_DATA_RAM", "base", 0xE3200000L, "len", 0x3200000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"C6_PROG_RAM", Global.newObject("name", "C6_PROG_RAM", "base", 0xE6400000L, "len", 0x3200000L, "space", "code", "access", "RWX")}), Global.newArray(new Object[]{"C7_HEAP_RAM", Global.newObject("name", "C7_HEAP_RAM", "base", 0xF0000000L, "len", 0xA00000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"C7_DATA_RAM", Global.newObject("name", "C7_DATA_RAM", "base", 0xF0A00000L, "len", 0xA00000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"C7_PROG_RAM", Global.newObject("name", "C7_PROG_RAM", "base", 0xF1400000L, "len", 0xA00000L, "space", "code", "access", "RWX")}), Global.newArray(new Object[]{"CORE_HEALTH", Global.newObject("name", "CORE_HEALTH", "base", 0xF1E00000L, "len", 0x400L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"CX_CRITICAL_SECTION", Global.newObject("name", "CX_CRITICAL_SECTION", "base", 0xF1E00400L, "len", 0xA00000L, "space", "data", "access", "RWX")}), Global.newArray(new Object[]{"CX_CRITICAL_SECTION_REFERENCE", Global.newObject("name", "CX_CRITICAL_SECTION_REFERENCE", "base", 0xF2800400L, "len", 0xA00000L, "space", "data", "access", "RWX")})}), "l2Mode", "0k", "l1PMode", "32k", "l1DMode", "32k")));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("myBoard_TRS.Platform")).bless();
        ((Value.Arr)om.findStrict("$packages", "myBoard_TRS")).add(pkgV);
    }

    public void exec( Scriptable xdcO, Session ses )
    {
        this.xdcO = xdcO;
        this.ses = ses;
        om = (Value.Obj)xdcO.get("om", null);

        Object o = om.geto("$name");
        String s = o instanceof String ? (String)o : null;
        isCFG = s != null && s.equals("cfg");
        isROV = s != null && s.equals("rov");

        $$IMPORTS();
        $$OBJECTS();
        Platform$$OBJECTS();
        Platform$$CONSTS();
        Platform$$CREATES();
        Platform$$FUNCTIONS();
        Platform$$SIZES();
        Platform$$TYPES();
        if (isROV) {
            Platform$$ROV();
        }//isROV
        $$SINGLETONS();
        Platform$$SINGLETONS();
        $$INITIALIZATION();
    }
}
