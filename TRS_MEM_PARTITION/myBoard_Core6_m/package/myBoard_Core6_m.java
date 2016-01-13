/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-z63
 */
import java.util.*;
import org.mozilla.javascript.*;
import xdc.services.intern.xsr.*;
import xdc.services.spec.Session;

public class myBoard_Core6_m
{
    static final String VERS = "@(#) xdc-z63\n";

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
        Global.callFxn("loadPackage", xdcO, "ti.platforms.generic");
        Global.callFxn("loadPackage", xdcO, "xdc.platform");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("myBoard_Core6_m.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("myBoard_Core6_m", new Value.Obj("myBoard_Core6_m", pkgP));
    }

    void Platform$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("myBoard_Core6_m.Platform.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("myBoard_Core6_m.Platform", new Value.Obj("myBoard_Core6_m.Platform", po));
        pkgV.bind("Platform", vo);
        // decls 
        om.bind("myBoard_Core6_m.Platform.Board", om.findStrict("xdc.platform.IPlatform.Board", "myBoard_Core6_m"));
        om.bind("myBoard_Core6_m.Platform.Memory", om.findStrict("xdc.platform.IPlatform.Memory", "myBoard_Core6_m"));
        // insts 
        Object insP = om.bind("myBoard_Core6_m.Platform.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("myBoard_Core6_m.Platform$$Object", new Proto.Obj());
        Object objP = om.bind("myBoard_Core6_m.Platform.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("myBoard_Core6_m.Platform$$Params", new Proto.Obj());
        om.bind("myBoard_Core6_m.Platform.Params", new Proto.Str(po, true));
    }

    void Platform$$CONSTS()
    {
        // module Platform
    }

    void Platform$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("myBoard_Core6_m.Platform$$create", new Proto.Fxn(om.findStrict("myBoard_Core6_m.Platform.Module", "myBoard_Core6_m"), om.findStrict("myBoard_Core6_m.Platform.Instance", "myBoard_Core6_m"), 2, 1, false));
                fxn.addArg(0, "name", $$T_Str, $$UNDEF);
                fxn.addArg(1, "__params", (Proto)om.findStrict("myBoard_Core6_m.Platform.Params", "myBoard_Core6_m"), Global.newObject());
        sb = new StringBuilder();
        sb.append("myBoard_Core6_m$Platform$$create = function( name, __params ) {\n");
            sb.append("var __mod = xdc.om['myBoard_Core6_m.Platform'];\n");
            sb.append("var __inst = xdc.om['myBoard_Core6_m.Platform.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['myBoard_Core6_m']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {name:name});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("__inst.externalMemoryMap = __mod.PARAMS.externalMemoryMap;\n");
            sb.append("__inst.customMemoryMap = __mod.PARAMS.customMemoryMap;\n");
            sb.append("__inst.renameMap = __mod.PARAMS.renameMap;\n");
            sb.append("__inst.dataMemory = __mod.PARAMS.dataMemory;\n");
            sb.append("__inst.codeMemory = __mod.PARAMS.codeMemory;\n");
            sb.append("__inst.stackMemory = __mod.PARAMS.stackMemory;\n");
            sb.append("__inst.sectMap = __mod.PARAMS.sectMap;\n");
            sb.append("__inst.peripherals = __mod.PARAMS.peripherals;\n");
            sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [name]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("myBoard_Core6_m.Platform$$construct", new Proto.Fxn(om.findStrict("myBoard_Core6_m.Platform.Module", "myBoard_Core6_m"), null, 3, 1, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("myBoard_Core6_m.Platform$$Object", "myBoard_Core6_m"), null);
                fxn.addArg(1, "name", $$T_Str, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("myBoard_Core6_m.Platform.Params", "myBoard_Core6_m"), Global.newObject());
        sb = new StringBuilder();
        sb.append("myBoard_Core6_m$Platform$$construct = function( __obj, name, __params ) {\n");
            sb.append("var __mod = xdc.om['myBoard_Core6_m.Platform'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {name:name});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("__inst.externalMemoryMap = __mod.PARAMS.externalMemoryMap;\n");
            sb.append("__inst.customMemoryMap = __mod.PARAMS.customMemoryMap;\n");
            sb.append("__inst.renameMap = __mod.PARAMS.renameMap;\n");
            sb.append("__inst.dataMemory = __mod.PARAMS.dataMemory;\n");
            sb.append("__inst.codeMemory = __mod.PARAMS.codeMemory;\n");
            sb.append("__inst.stackMemory = __mod.PARAMS.stackMemory;\n");
            sb.append("__inst.sectMap = __mod.PARAMS.sectMap;\n");
            sb.append("__inst.peripherals = __mod.PARAMS.peripherals;\n");
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

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "myBoard_Core6_m/Platform.xs");
        om.bind("myBoard_Core6_m.Platform$$capsule", cap);
        po = (Proto.Obj)om.findStrict("myBoard_Core6_m.Platform.Module", "myBoard_Core6_m");
        po.init("myBoard_Core6_m.Platform.Module", om.findStrict("xdc.platform.IPlatform.Module", "myBoard_Core6_m"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("CPU", (Proto)om.findStrict("ti.platforms.generic.Platform.Instance", "myBoard_Core6_m"), $$UNDEF, "wh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("myBoard_Core6_m.Platform$$create", "myBoard_Core6_m"), Global.get("myBoard_Core6_m$Platform$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("myBoard_Core6_m.Platform$$construct", "myBoard_Core6_m"), Global.get("myBoard_Core6_m$Platform$$construct"));
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("myBoard_Core6_m.Platform$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("myBoard_Core6_m.Platform$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("myBoard_Core6_m.Platform$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("myBoard_Core6_m.Platform$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("myBoard_Core6_m.Platform.Instance", "myBoard_Core6_m");
        po.init("myBoard_Core6_m.Platform.Instance", om.findStrict("xdc.platform.IPlatform.Instance", "myBoard_Core6_m"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("codeMemory", $$T_Str, "L2RAM", "wh");
        po.addFld("dataMemory", $$T_Str, "C6_DATA_RAM", "wh");
        po.addFld("stackMemory", $$T_Str, "L2RAM", "wh");
        po.addFld("l2Mode", $$T_Str, "64k", "wh");
        po.addFld("l1PMode", $$T_Str, "32k", "wh");
        po.addFld("l1DMode", $$T_Str, "16k", "wh");
                fxn = Global.get(cap, "getCpuDataSheet");
                if (fxn != null) po.addFxn("getCpuDataSheet", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getCpuDataSheet", "myBoard_Core6_m"), fxn);
                fxn = Global.get(cap, "getCreateArgs");
                if (fxn != null) po.addFxn("getCreateArgs", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getCreateArgs", "myBoard_Core6_m"), fxn);
                fxn = Global.get(cap, "getExeContext");
                if (fxn != null) po.addFxn("getExeContext", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getExeContext", "myBoard_Core6_m"), fxn);
                fxn = Global.get(cap, "getExecCmd");
                if (fxn != null) po.addFxn("getExecCmd", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getExecCmd", "myBoard_Core6_m"), fxn);
                fxn = Global.get(cap, "getLinkTemplate");
                if (fxn != null) po.addFxn("getLinkTemplate", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getLinkTemplate", "myBoard_Core6_m"), fxn);
        po = (Proto.Obj)om.findStrict("myBoard_Core6_m.Platform$$Params", "myBoard_Core6_m");
        po.init("myBoard_Core6_m.Platform.Params", om.findStrict("xdc.platform.IPlatform$$Params", "myBoard_Core6_m"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("codeMemory", $$T_Str, "L2RAM", "wh");
        po.addFld("dataMemory", $$T_Str, "C6_DATA_RAM", "wh");
        po.addFld("stackMemory", $$T_Str, "L2RAM", "wh");
        po.addFld("l2Mode", $$T_Str, "64k", "wh");
        po.addFld("l1PMode", $$T_Str, "32k", "wh");
        po.addFld("l1DMode", $$T_Str, "16k", "wh");
        po = (Proto.Obj)om.findStrict("myBoard_Core6_m.Platform$$Object", "myBoard_Core6_m");
        po.init("myBoard_Core6_m.Platform.Object", om.findStrict("myBoard_Core6_m.Platform.Instance", "myBoard_Core6_m"));
                fxn = Global.get(cap, "getCpuDataSheet");
                if (fxn != null) po.addFxn("getCpuDataSheet", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getCpuDataSheet", "myBoard_Core6_m"), fxn);
                fxn = Global.get(cap, "getCreateArgs");
                if (fxn != null) po.addFxn("getCreateArgs", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getCreateArgs", "myBoard_Core6_m"), fxn);
                fxn = Global.get(cap, "getExeContext");
                if (fxn != null) po.addFxn("getExeContext", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getExeContext", "myBoard_Core6_m"), fxn);
                fxn = Global.get(cap, "getExecCmd");
                if (fxn != null) po.addFxn("getExecCmd", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getExecCmd", "myBoard_Core6_m"), fxn);
                fxn = Global.get(cap, "getLinkTemplate");
                if (fxn != null) po.addFxn("getLinkTemplate", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getLinkTemplate", "myBoard_Core6_m"), fxn);
    }

    void Platform$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("myBoard_Core6_m.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "myBoard_Core6_m"));
        pkgP.bind("$capsule", $$UNDEF);
        pkgV.init2(pkgP, "myBoard_Core6_m", Value.DEFAULT, false);
        pkgV.bind("$name", "myBoard_Core6_m");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "myBoard_Core6_m.");
        pkgV.bind("$vers", Global.newArray());
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['myBoard_Core6_m'];\n");
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

        vo = (Value.Obj)om.findStrict("myBoard_Core6_m.Platform", "myBoard_Core6_m");
        po = (Proto.Obj)om.findStrict("myBoard_Core6_m.Platform.Module", "myBoard_Core6_m");
        vo.init2(po, "myBoard_Core6_m.Platform", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("myBoard_Core6_m.Platform$$capsule", "myBoard_Core6_m"));
        vo.bind("Instance", om.findStrict("myBoard_Core6_m.Platform.Instance", "myBoard_Core6_m"));
        vo.bind("Params", om.findStrict("myBoard_Core6_m.Platform.Params", "myBoard_Core6_m"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("myBoard_Core6_m.Platform.Params", "myBoard_Core6_m")).newInstance());
        vo.bind("$package", om.findStrict("myBoard_Core6_m", "myBoard_Core6_m"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("Board", om.findStrict("xdc.platform.IPlatform.Board", "myBoard_Core6_m"));
        tdefs.add(om.findStrict("xdc.platform.IPlatform.Board", "myBoard_Core6_m"));
        vo.bind("Memory", om.findStrict("xdc.platform.IPlatform.Memory", "myBoard_Core6_m"));
        tdefs.add(om.findStrict("xdc.platform.IPlatform.Memory", "myBoard_Core6_m"));
        vo.bind("MemoryMap", om.findStrict("xdc.platform.IPlatform.MemoryMap", "myBoard_Core6_m"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.platform");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "myBoard_Core6_m")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("myBoard_Core6_m.Platform$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("myBoard_Core6_m.Platform.Object", "myBoard_Core6_m"));
        pkgV.bind("Platform", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Platform");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("myBoard_Core6_m.Platform", "myBoard_Core6_m"));
        vo = (Value.Obj)om.findStrict("myBoard_Core6_m.Platform", "myBoard_Core6_m");
        Global.put(vo, "CPU", Global.callFxn("create", (Scriptable)om.find("ti.platforms.generic.Platform"), "CPU", Global.newObject("clockRate", 1000L, "catalogName", "ti.catalog.c6000", "deviceName", "TMS320C6678", "customMemoryMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"L1D_RAM", Global.newObject("name", "L1D_RAM", "base", 0x00F00000L, "len", 0x8000L, "space", "data", "access", "RW")}), Global.newArray(new Object[]{"L1P_RAM", Global.newObject("name", "L1P_RAM", "base", 0x00E00000L, "len", 0x8000L, "space", "code", "access", "RWX")}), Global.newArray(new Object[]{"L2RAM", Global.newObject("name", "L2RAM", "base", 0x00800000L, "len", 0x80000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"C6_DATA_RAM", Global.newObject("name", "C6_DATA_RAM", "base", 0x84800000L, "len", 0x400000L, "space", "data", "access", "RW")}), Global.newArray(new Object[]{"CX_CRITICAL_SECTION_REFERENCE", Global.newObject("name", "CX_CRITICAL_SECTION_REFERENCE", "base", 0x80100000L, "len", 0x1000L, "space", "data", "access", "RW")}), Global.newArray(new Object[]{"C6_NON_CACHE", Global.newObject("name", "C6_NON_CACHE", "base", 0x86800000L, "len", 0x400000L, "space", "data", "access", "RW")}), Global.newArray(new Object[]{"MSMCSRAM", Global.newObject("name", "MSMCSRAM", "base", 0x0c000000L, "len", 0x400000L, "space", "data", "access", "RW")}), Global.newArray(new Object[]{"SM_HEAP1", Global.newObject("name", "SM_HEAP1", "base", 0x82000000L, "len", 0x400000L, "space", "data", "access", "RW")}), Global.newArray(new Object[]{"SM_HEAP2", Global.newObject("name", "SM_HEAP2", "base", 0x82400000L, "len", 0x400000L, "space", "data", "access", "RW")}), Global.newArray(new Object[]{"SM_HEAP3", Global.newObject("name", "SM_HEAP3", "base", 0x82800000L, "len", 0x400000L, "space", "data", "access", "RW")}), Global.newArray(new Object[]{"SM_HEAP4", Global.newObject("name", "SM_HEAP4", "base", 0x82C00000L, "len", 0x400000L, "space", "data", "access", "RW")})}), "l2Mode", "64k", "l1PMode", "32k", "l1DMode", "16k")));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("myBoard_Core6_m.Platform")).bless();
        ((Value.Arr)om.findStrict("$packages", "myBoard_Core6_m")).add(pkgV);
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
