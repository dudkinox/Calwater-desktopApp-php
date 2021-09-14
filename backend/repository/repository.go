package repository

import (
	"backend/model"
	"context"
)

type CrudRepositoryI interface {
	InfoData(ctx context.Context) (crudResp model.GetInfoResponse, err error)
	InsertInfoData(ctx context.Context, model model.ModelInfo) (ID string, err error)
	DeleteInfoData(ctx context.Context, ID string) (Status string, err error)
}
