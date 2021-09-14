package usecase

import (
	"backend/model"
	"backend/repository"
	"context"
)

type CrudUseCase struct {
	config   *model.EnvConfig
	crudRepo repository.CrudRepositoryI
}

func NewCrudUseCase(config *model.EnvConfig, crudRepo repository.CrudRepositoryI) CrudUseCaseI {
	return &CrudUseCase{
		config:   config,
		crudRepo: crudRepo,
	}
}

func (cuc *CrudUseCase) GetHealthCheck(ctx context.Context) (err error) {
	return
}

func (cuc *CrudUseCase) InfoUC(ctx context.Context) (resp model.GetInfoResponse, err error) {
	if ctx == nil {
		ctx = context.Background()
	}
	list, err := cuc.crudRepo.InfoData(ctx)
	if err != nil {
		return resp, err
	}

	return list, err
}

func (cuc *CrudUseCase) InsertInfoUC(ctx context.Context, req model.ModelInfo) (ID string, err error) {
	if ctx == nil {
		ctx = context.Background()
	}

	reselt, err := cuc.crudRepo.InsertInfoData(ctx, req)
	if err != nil {
		return "ผิดพลาด", err
	}

	return reselt, nil
}
