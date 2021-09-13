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

func (cuc *CrudUseCase) GetNameUC(ctx context.Context) (resp model.GetNameResponse, err error) {
	if ctx == nil {
		ctx = context.Background()
	}
	list, err := cuc.crudRepo.GetNameData(ctx)
	if err != nil {
		return resp, err
	}

	return list, err
}
