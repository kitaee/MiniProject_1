# -*- coding: utf-8 -*-
"""Manager 소스·ICD XML 재생성 (UTF-8) — ICD/1팀 ICD.xlsx msgID(10진수) 기준"""
from dataclasses import dataclass
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent


@dataclass(frozen=True)
class NomField:
    name: str
    data_type: str
    size: str | None = None


@dataclass(frozen=True)
class WireMessage:
    id: str
    name: str
    kind: str  # interaction | object
    sem: str
    fields: tuple[NomField, ...]


def f(name: str, data_type: str, size: str | None = None) -> NomField:
    return NomField(name, data_type, size)


WIRE_MESSAGES: tuple[WireMessage, ...] = (
    WireMessage("1001", "DeployScenarioRequest", "interaction", "통합통제기→모의기 시나리오 배포", (
        f("MessageHeader", "MessageHeaderStruct"),
        f("Airthreat", "AirthreatStruct"),
        f("RadarPositionLatitude", "float"),
        f("RadarPositionLongitude", "float"),
        f("LauncherPositionLatitude", "float"),
        f("LauncherPositionLongitude", "float"),
    )),
    WireMessage("1002", "StartSimulationRequest", "interaction", "통합통제기→모의기 시뮬레이션 시작", (
        f("MessageHeader", "MessageHeaderStruct"),
    )),
    WireMessage("1003", "StopSimulationRequest", "interaction", "통합통제기→모의기 시뮬레이션 정지", (
        f("MessageHeader", "MessageHeaderStruct"),
    )),
    WireMessage("1401", "LaunchMissileRequest", "interaction", "통합통제기→발사대 모의기 발사 명령", (
        f("MessageHeader", "MessageHeaderStruct"),
    )),
    WireMessage("1501", "UplinkInfo", "object", "통합통제기→레이더 모의기 업링크(주기)", (
        f("MessageHeader", "MessageHeaderStruct"),
        f("UplinkInfo", "UplinkInfoStruct"),
    )),
    WireMessage("2101", "ScenarioACK", "interaction", "ATS→통합통제기 시나리오 ACK", (
        f("MessageHeader", "MessageHeaderStruct"),
    )),
    WireMessage("2501", "ATInfo", "object", "공중위협→레이더 공중위협 객체 정보(주기)", (
        f("MessageHeader", "MessageHeaderStruct"),
        f("AirthreatID", "uint"),
        f("AirthreatXPos", "float"),
        f("AirthreatYPos", "float"),
        f("AirthreatZPos", "float"),
        f("AirthreatVelocity", "float"),
    )),
    WireMessage("3101", "ScenarioACK", "interaction", "유도탄→통합통제기 시나리오 ACK", (
        f("MessageHeader", "MessageHeaderStruct"),
    )),
    WireMessage("3201", "DetonationInfo", "interaction", "유도탄→공중위협 요격 결과", (
        f("MessageHeader", "MessageHeaderStruct"),
        f("MissleID", "uint"),
        f("TargetID", "uint"),
    )),
    WireMessage("3501", "DownlinkInfo", "object", "유도탄→레이더 유도탄 좌표(주기)", (
        f("MessageHeader", "MessageHeaderStruct"),
        f("DownlinkInfo", "DownlinkInfoStruct"),
    )),
    WireMessage("4101", "ScenarioACK", "interaction", "발사대→통합통제기 시나리오 ACK", (
        f("MessageHeader", "MessageHeaderStruct"),
    )),
    WireMessage("4102", "MissileQuantityInfo", "interaction", "발사대→통합통제기 유도탄 재고", (
        f("MessageHeader", "MessageHeaderStruct"),
        f("MissileQuantity", "uint"),
    )),
    WireMessage("4301", "LaunchMissile", "interaction", "발사대→유도탄 발사 정보", (
        f("MessageHeader", "MessageHeaderStruct"),
        f("AirthreatID", "uint"),
        f("AirthreatXpos", "float"),
        f("AirthreatYPos", "float"),
        f("AirthreatZPos", "float"),
        f("MissleID", "uint"),
        f("LCSXpos", "float"),
        f("LCSYPos", "float"),
        f("LCSZPos", "float"),
    )),
    WireMessage("5101", "ScenarioACK", "interaction", "레이더→통합통제기 시나리오 ACK", (
        f("MessageHeader", "MessageHeaderStruct"),
    )),
    WireMessage("5102", "RadarDetectionInfo", "object", "레이더→통합통제기 탐지 결과(주기)", (
        f("MessageHeader", "MessageHeaderStruct"),
        f("RadarDetection", "DetectedTargetStruct"),
    )),
    WireMessage("5103", "DownlinkInfo", "object", "레이더→통합통제기 유도탄 좌표(주기)", (
        f("MessageHeader", "MessageHeaderStruct"),
        f("DownlinkInfo", "DownlinkInfoStruct"),
    )),
    WireMessage("5301", "UplinkInfo", "object", "레이더→유도탄 업링크(주기)", (
        f("MessageHeader", "MessageHeaderStruct"),
        f("UplinkInfo", "UplinkInfoStruct"),
    )),
)

MSG_BY_ID = {m.id: m for m in WIRE_MESSAGES}
ACK_ALL = ("2101", "3101", "4101", "5101")

MANAGER_MSGS = {
    "UIManager": {"role": "C# WPF ↔ MEB 브릿지", "pub": ("1001", "1002", "1003", "1401", "1501"), "sub": ACK_ALL + ("4102", "5102", "5103")},
    "ScenarioManager": {"role": "시나리오 저장·배포", "pub": ("1001",), "sub": ACK_ALL},
    "ControlManager": {"role": "시뮬레이션 제어·발사 명령", "pub": ("1002", "1003", "1401")},
    "StatusManager": {"role": "모의기 상태·트랙·Ack 집계", "sub": ACK_ALL + ("4102", "5102", "5103")},
    "SimulationManager": {"role": "시뮬레이션 상태·시나리오·Ack", "pub": (), "sub": ("1001", "1002", "1003")},
    "ATSModelManager": {"role": "ATS 물리/행동 모델", "pub": ("2501",)},
    "LaunchManager": {"role": "발사 제어", "sub": ("1401",), "pub": ("4301",)},
    "LCSModelManager": {"role": "LCS 물리/행동 모델", "pub": ("4102",)},
    "DetectManager": {"role": "레이더 탐지", "pub": ("5102",)},
    "DataLinkManager": {"role": "데이터링크", "pub": ("5301", "5103"), "sub": ("1501", "2501", "3501")},
    "MFRSModelManager": {"role": "MFRS 물리/행동 모델", "pub": ()},
    "MSSModelManager": {"role": "MSS 물리/행동 모델", "pub": ()},
    "DetonationManager": {"role": "요격·폭발 결과", "pub": ("3201",)},
}

SIM_MANAGER_ACK = {"ats": "2101", "mss": "3101", "lcs": "4101", "mfrs": "5101"}

SIM_MANAGERS = {
    "tcc": ("UIManager", "ControlManager", "ScenarioManager", "StatusManager"),
    "ats": ("SimulationManager", "ATSModelManager"),
    "lcs": ("SimulationManager", "LaunchManager", "LCSModelManager"),
    "mfrs": ("SimulationManager", "DetectManager", "DataLinkManager", "MFRSModelManager"),
    "mss": ("SimulationManager", "LaunchManager", "DataLinkManager", "MSSModelManager", "DetonationManager"),
}


def fmt_field(field: NomField, tag: str) -> str:
    if field.size:
        return f'      <{tag} name="{field.name}" semantics="{field.name}" dataType="{field.data_type}" size="{field.size}"/>'
    return f'      <{tag} name="{field.name}" semantics="{field.name}" dataType="{field.data_type}"/>'


def fmt_message(msg: WireMessage, sharing: str) -> str:
    if msg.kind == "object":
        open_tag = (
            f'    <NOM:object name="{msg.name}" id="{msg.id}" semantics="{msg.sem}" '
            f'sharing="{sharing}" orderType="Receive" alignment="false">'
        )
        close_tag = "    </NOM:object>"
        tag = "NOM:attribute"
    else:
        open_tag = (
            f'    <NOM:interaction name="{msg.name}" id="{msg.id}" semantics="{msg.sem}" '
            f'sharing="{sharing}" orderType="Receive" alignment="false">'
        )
        close_tag = "    </NOM:interaction>"
        tag = "NOM:parameter"
    lines = [open_tag, *(fmt_field(field, tag) for field in msg.fields), close_tag]
    return "\n".join(lines)


def manager_xml(name: str, spec: dict) -> str:
    pub = spec.get("pub", ())
    sub = spec.get("sub", ())
    both = spec.get("both", ())
    objs: list[str] = []
    ixs: list[str] = []
    for mid in (*pub, *sub, *both):
        msg = MSG_BY_ID[mid]
        sharing = "Publish" if mid in pub else "Subscribe" if mid in sub else "PublishSubscribe"
        block = fmt_message(msg, sharing)
        (objs if msg.kind == "object" else ixs).append(block)
    obj_block = "\n".join(objs) + ("\n" if objs else "")
    ix_block = "\n".join(ixs) + ("\n" if ixs else "")
    return f"""<?xml version="1.0" encoding="UTF-8"?>
<NOM:Nex1ObjectModel xmlns:NOM="lignex1.sw.nframework.NOM" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="lignex1.sw.nframework.NOM NOM.xsd" version="0.1" name="{name}" date="2026-06-18" author="SimulatorSuite">
  <NOM:objects>
{obj_block}  </NOM:objects>
  <NOM:interactions>
{ix_block}  </NOM:interactions>
  <NOM:dataTypes>
    <NOM:basicTypes/>
    <NOM:enumerationTypes/>
    <NOM:complexTypes/>
  </NOM:dataTypes>
  <NOM:notes>
  </NOM:notes>
</NOM:Nex1ObjectModel>
"""


def udp_xml() -> str:
    objs = [fmt_message(m, "PublishSubscribe") for m in WIRE_MESSAGES if m.kind == "object"]
    ixs = [fmt_message(m, "PublishSubscribe") for m in WIRE_MESSAGES if m.kind == "interaction"]
    obj_block = "\n".join(objs) + "\n"
    ix_block = "\n".join(ixs) + "\n"
    return f"""<?xml version="1.0" encoding="UTF-8"?>
<NOM:Nex1ObjectModel xmlns:NOM="lignex1.sw.nframework.NOM" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="lignex1.sw.nframework.NOM NOM.xsd" version="0.1" name="UDPCommunicationManager" date="2026-06-18" author="SimulatorSuite">
  <NOM:objects>
{obj_block}  </NOM:objects>
  <NOM:interactions>
{ix_block}  </NOM:interactions>
  <NOM:dataTypes>
    <NOM:basicTypes/>
    <NOM:enumerationTypes/>
    <NOM:complexTypes/>
  </NOM:dataTypes>
  <NOM:notes>
  </NOM:notes>
</NOM:Nex1ObjectModel>
"""


def manager_h(name: str, role: str) -> str:
    return f"""#pragma once
#include <nFramework/BaseManager.h>
#include <nFramework/mec/MECComponent.h>
#include <nFramework/nom/NOMMain.h>

using namespace nframework;
using namespace nom;

// 역할: {role}

class BASEMGRDLL_API {name} : public BaseManager
{{
public:
    {name}();
    ~{name}() override;

    std::shared_ptr<NOM> registerMsg(std::wstring) override;
    void discoverMsg(std::shared_ptr<NOM>) override;
    void updateMsg(std::shared_ptr<NOM>) override;
    void reflectMsg(std::shared_ptr<NOM>) override;
    void deleteMsg(std::shared_ptr<NOM>) override;
    void removeMsg(std::shared_ptr<NOM>) override;
    void sendMsg(std::shared_ptr<NOM>) override;
    void recvMsg(std::shared_ptr<NOM>) override;
    void setUserName(std::wstring) override;
    tstring getUserName() override;
    void setData(void*) override;
    bool start() override;
    bool stop() override;
    void setMEBComponent(IMEBComponent*) override;

private:
    IMEBComponent* meb{{ nullptr }};
    MECComponent* mec{{ nullptr }};
    tstring name;
}};
"""


def manager_cpp(name: str, role: str) -> str:
    return f"""#include "{name}.h"

// 역할: {role}
// BaseManager MEC 위임만 구현. 업무 로직은 추후 reflectMsg/recvMsg/start 에 추가.

{name}::{name}()
{{
    mec = new MECComponent;
    mec->setUser(this);
    setUserName(L"{name}");
}}

{name}::~{name}()
{{
    delete mec;
    mec = nullptr;
    meb = nullptr;
}}

std::shared_ptr<NOM> {name}::registerMsg(std::wstring msgName) {{ return mec->registerMsg(msgName); }}
void {name}::discoverMsg(std::shared_ptr<NOM> nomMsg) {{ mec->discoverMsg(nomMsg); }}
void {name}::updateMsg(std::shared_ptr<NOM> nomMsg) {{ mec->updateMsg(nomMsg); }}
void {name}::reflectMsg(std::shared_ptr<NOM>) {{}}
void {name}::deleteMsg(std::shared_ptr<NOM> nomMsg) {{ mec->deleteMsg(nomMsg); }}
void {name}::removeMsg(std::shared_ptr<NOM> nomMsg) {{ mec->removeMsg(nomMsg); }}
void {name}::sendMsg(std::shared_ptr<NOM> nomMsg) {{ mec->sendMsg(nomMsg); }}
void {name}::recvMsg(std::shared_ptr<NOM>) {{}}
void {name}::setUserName(std::wstring userName) {{ name = userName; }}
tstring {name}::getUserName() {{ return name; }}
void {name}::setData(void*) {{}}
bool {name}::start() {{ return true; }}
bool {name}::stop() {{ return true; }}
void {name}::setMEBComponent(IMEBComponent* realMEB) {{ meb = realMEB; mec->setMEB(meb); }}

extern "C" BASEMGRDLL_API BaseManager* createObject() {{ return new {name}; }}
extern "C" BASEMGRDLL_API void deleteObject(BaseManager* mgr) {{ delete mgr; }}
"""


def build_spec(sim: str, mgr: str) -> dict:
    base = MANAGER_MSGS[mgr]
    spec = {
        "role": base["role"],
        "pub": list(base.get("pub", ())),
        "sub": list(base.get("sub", ())),
        "both": list(base.get("both", ())),
    }
    if mgr == "SimulationManager":
        if sim in SIM_MANAGER_ACK:
            spec["pub"].append(SIM_MANAGER_ACK[sim])
        if sim == "lcs":
            spec["sub"].append("1401")
        if sim == "ats":
            spec["sub"].append("3201")
    if mgr == "LaunchManager" and sim == "mss":
        spec["sub"].append("4301")
        spec["pub"].append("3501")
    if mgr == "DataLinkManager" and sim == "mss":
        spec["pub"] = ["3501"]
        spec["sub"] = ["5301"]
    return spec


def write_utf8(path: Path, text: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8", newline="\n")


def main() -> None:
    for sim, mgrs in SIM_MANAGERS.items():
        for mgr in mgrs:
            spec = build_spec(sim, mgr)
            src = ROOT / sim / "src" / "Managers" / mgr
            write_utf8(src / f"{mgr}.h", manager_h(mgr, spec["role"]))
            write_utf8(src / f"{mgr}.cpp", manager_cpp(mgr, spec["role"]))
            write_utf8(ROOT / sim / "bin" / mgr / f"{mgr}.xml", manager_xml(mgr, spec))
        write_utf8(ROOT / sim / "bin" / "UDPCommunicationManager" / "UDPCommunicationManager.xml", udp_xml())
    print("Done: ICD Excel msgID (decimal) applied")


if __name__ == "__main__":
    main()
