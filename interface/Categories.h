#pragma once

#include <cp3_llbb/Framework/interface/MuonsProducer.h>
#include <cp3_llbb/Framework/interface/ElectronsProducer.h>

class MuMuCategory: public Category {
    virtual bool event_in_category(const ProducersManager& producers) const override {
        const MuonsProducer& muons = dynamic_cast<const MuonsProducer&>(producers.get("muons"));
        const ElectronsProducer& electrons = dynamic_cast<const ElectronsProducer&>(producers.get("electrons"));
        if( muons.p4.size() >= 2 )
        {
            if( electrons.p4.size() >= 1 ) // if there is electrons at all, check the muons are the leading leptons
            {
                if( muons.p4[1].Pt() > electrons.p4[0].Pt() )
                    return true;
            } else {
                return true;
            }
        }
        return false;
    };
};

class MuElCategory: public Category {
    virtual bool event_in_category(const ProducersManager& producers) const override {
        const MuonsProducer& muons = dynamic_cast<const MuonsProducer&>(producers.get("muons"));
        const ElectronsProducer& electrons = dynamic_cast<const ElectronsProducer&>(producers.get("electrons"));
        if( (muons.p4.size() == 1) && (electrons.p4.size() >= 1) )
        {
            if( muons.p4[0].Pt() > electrons.p4[0].Pt() )
                return true;
        }
        else if( (muons.p4.size() >= 1) && (electrons.p4.size() >= 1) )
        {
            if( (muons.p4[0].Pt() > electrons.p4[0].Pt()) && (muons.p4[1].Pt() < electrons.p4[0].Pt()) )
              return true;
        }
        return false;
    };
};

class ElMuCategory: public Category {
    virtual bool event_in_category(const ProducersManager& producers) const override {
        const MuonsProducer& muons = dynamic_cast<const MuonsProducer&>(producers.get("muons"));
        const ElectronsProducer& electrons = dynamic_cast<const ElectronsProducer&>(producers.get("electrons"));
//        for( auto p4: muons.p4 )
//            std::cout << "muon p4.Pt()= " << p4.Pt() << std::endl;
//        for( auto p4: electrons.p4 )
//            std::cout << "electron p4.Pt()= " << p4.Pt() << std::endl;
        if( (electrons.p4.size() == 1) && (muons.p4.size() >= 1) )
        {
            if( electrons.p4[0].Pt() > muons.p4[0].Pt() )
                return true;
        }
        else if( (electrons.p4.size() >= 1) && (muons.p4.size() >= 1) )
        {
            if( (electrons.p4[0].Pt() > muons.p4[0].Pt()) && (electrons.p4[1].Pt() < muons.p4[0].Pt()) )
              return true;
        }
        return false;
    };
};

class ElElCategory: public Category {
    virtual bool event_in_category(const ProducersManager& producers) const override {
        const MuonsProducer& muons = dynamic_cast<const MuonsProducer&>(producers.get("muons"));
        const ElectronsProducer& electrons = dynamic_cast<const ElectronsProducer&>(producers.get("electrons"));
        if( electrons.p4.size() >= 2 )
        {
            if( muons.p4.size() >= 1 ) // if there is muons at all, check the electrons are the leading leptons
            {
                if( electrons.p4[1].Pt() > muons.p4[0].Pt() )
                    return true;
            } else {
                return true;
            }
        }
        return false;
    };
};
