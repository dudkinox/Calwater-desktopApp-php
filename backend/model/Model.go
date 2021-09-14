package model

import "go.mongodb.org/mongo-driver/bson/primitive"

type (
	GetNameResponse struct {
		Data []ModelSave `json:"table"`
	}
	ModelSave struct {
		Id   primitive.ObjectID `json:"_id,omitempty" bson:"_id,omitempty" validate:"required"`
		Name string             `json:"Name"`
	}
	GetInfoResponse struct {
		Data []ModelInfo `json:"wastewaterdata"`
	}
	ModelInfo struct {
		Id                       primitive.ObjectID     `json:"_id,omitempty" bson:"_id,omitempty" validate:"required"`
		Volume                   primitive.Decimal128   `json:"Volume"`
		Batch_No                 string                 `json:"Batch_No"`
		Meet_MOI_Spec            string                 `json:"Meet_MOI_Spec"`
		Sump_No                  string                 `json:"Sump_No"`
		Treatment_Date           string                 `json:"Treatment_Date"`
		Raw_Waste_Water_Analysis Raw_Waste_Water        `json:"Raw_Waste_Water_Analysis"`
		Treat_Water_Analysis     Treat_Water            `json:"Treat_Water_Analysis"`
		Process_Reagent          PROCESS_REAGENT_Object `json:"Process_Reagent"`
	}
)

type (
	Raw_Waste_Water struct {
		PH        primitive.Decimal128 `json:"pH"`
		Cyanide   primitive.Decimal128 `json:"Cyanide"`
		Total_Cr  primitive.Decimal128 `json:"Total_Cr"`
		Cu        primitive.Decimal128 `json:"Cu"`
		Mn        primitive.Decimal128 `json:"Mn"`
		Ni        primitive.Decimal128 `json:"Ni"`
		Pb        primitive.Decimal128 `json:"Pb"`
		Zn        primitive.Decimal128 `json:"Zn"`
		Sum_Metal primitive.Decimal128 `json:"Sum_Metal"`
		COD       int32                `json:"COD"`
		SS        int32                `json:"SS"`
		TDS       int32                `json:"TDS"`
	}
)

type (
	Treat_Water struct {
		PH        PH_Object        `json:"pH"`
		Cyanide   CYANIDE_Object   `json:"Cyanide"`
		Total_Cr  TOTAL_CR_Object  `json:"Total_Cr"`
		Cu        CU_Object        `json:"Cu"`
		Mn        MN_Object        `json:"Mn"`
		Ni        NI_Object        `json:"Ni"`
		Pb        PB_Object        `json:"Pb"`
		Zn        ZN_Object        `json:"Zn"`
		Sum_Metal SUM_METAL_Object `json:"Sum_Metal"`
		COD       COD_Object       `json:"COD"`
		SS        SS_Object        `json:"SS"`
		TDS       TDS_Object       `json:"TDS"`
	}
	PH_Object struct {
		None primitive.Decimal128 `json:"None"`
	}
	CYANIDE_Object struct {
		No_0_2 primitive.Decimal128 `json:"0.2"`
	}
	TOTAL_CR_Object struct {
		No_0_25 primitive.Decimal128 `json:"0.25"`
	}
	CU_Object struct {
		No_2_0 primitive.Decimal128 `json:"2.0"`
	}
	MN_Object struct {
		No_5_0 primitive.Decimal128 `json:"5.0"`
	}
	NI_Object struct {
		No_1_0 primitive.Decimal128 `json:"1.0"`
	}
	PB_Object struct {
		No_0_2 primitive.Decimal128 `json:"0.2"`
	}
	ZN_Object struct {
		No_5_0 primitive.Decimal128 `json:"5.0"`
	}
	SUM_METAL_Object struct {
		None primitive.Decimal128 `json:"None"`
	}
	COD_Object struct {
		None int32 `json:"None"`
	}
	SS_Object struct {
		None int32 `json:"None"`
	}
	TDS_Object struct {
		None int32 `json:"None"`
	}
)

type (
	PROCESS_REAGENT_Object struct {
		Lime    LIME_Object    `json:"Lime"`
		NaOCl   NAOCL_Object   `json:"NaOCl"`
		H2SO4   H2SO4_Object   `json:"H2SO4"`
		FeSO4   FESO4_Object   `json:"FeSO4"`
		Na2S2O5 NA2S2O5_Object `json:"Na2S2O5"`
		Polymer POLYMER_Object `json:"Polymer"`
	}
	LIME_Object struct {
		Kgs int32 `json:"kgs"`
	}
	NAOCL_Object struct {
		Kgs int32 `json:"kgs"`
	}
	H2SO4_Object struct {
		Kgs string `json:"kgs"`
	}
	FESO4_Object struct {
		Kgs int32 `json:"kgs"`
	}
	NA2S2O5_Object struct {
		Kgs string `json:"kgs"`
	}
	POLYMER_Object struct {
		Kgs primitive.Decimal128 `json:"kgs"`
	}
)
